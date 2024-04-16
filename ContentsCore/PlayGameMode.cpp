#include "PreCompile.h"
#include "PlayGameMode.h"
#include "BabaBase.h"
#include "PlayBack.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Rock.h"
#include "TileMap.h"
#include <iterator>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineCore.h>

APlayGameMode::APlayGameMode()
{}

APlayGameMode::~APlayGameMode()
{}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.0f, 0.0f, -100.0f));

	std::shared_ptr<ABabaBase> Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	Player->StateInit(BabaState::IsBaba);
	Player->ActiveStateInit(ActiveState{true, true, true});
	Player->SetBabaLocation(0, 2, 'D');
	Baba_Actors[Player->GetTile64()].push_back(Player.get());



	//Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	//Player->StateInit(true, true, true);
	//Player->SetBabaLocation(4, 2, 'W');
	//Baba_Actors[Player->GetTile64()].push_back(Player.get());

	Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	Player->StateInit(BabaState::IsRock);
	Player->ActiveStateInit(ActiveState{ false, true, false });
	Player->SetBabaLocation(8, 4, 'W');
	Baba_Actors[Player->GetTile64()].push_back(Player.get());

	Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	Player->StateInit(BabaState::IsRock);
	Player->ActiveStateInit(ActiveState{ false, true, false });
	Player->SetBabaLocation(5, 4, 'W');
	Baba_Actors[Player->GetTile64()].push_back(Player.get());

	//Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	//Player->StateInit(false, true, false);
	//Player->SetBabaLocation(5, 5, 'W');
	//Baba_Actors[Player->GetTile64()].push_back(Player.get());

	//std::shared_ptr<ABabaBase> Back = GetWorld()->SpawnActor<ABabaBase>("PlayBack");
	//Back->SetActorLocation({ 0.0f, 0.0f, 500.0f });
	TileMap::TileSet(10, 10);

	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	if (ContentsHelper::Time >= 1) {
		CanInput = true;
	}
	else {
		CanInput = false;
	}
	if (CanInput == true) {
	BabaInputCheck();
	}
	DebugMessageFunction();
}

void APlayGameMode::Baba_Input()
{
	switch (Key)
	{
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		Stack_Push(Key);
		break;
	case 'Z':
		Stack_Pop();
		break;
	default:
		break;
	}
}

void APlayGameMode::Stack_Push(char _Key)
{
	Stack_Input.push(_Key);
	ContentsHelper::Time = 0.f;

	for (std::pair<const __int64, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			_BabaBase->SetKey(_Key);
			_BabaBase->LerpMove();
		}
	}

}
void APlayGameMode::Stack_Pop()
{
	char Temp_Key;
	if (Stack_Input.empty() != true) {
		Temp_Key = Stack_Input.top();
		Stack_Input.pop();
		ContentsHelper::Time = 0.f;
		for (std::pair<const __int64, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			if (BabaBase.empty() == true) {
				continue;
			}
			for (ABabaBase*& _BabaBase : BabaBase) {
				_BabaBase->SetKey(Temp_Key);
				_BabaBase->PopLerpMove();
				Change_Baba.push_back(_BabaBase);
			}
		}
	}
}

void APlayGameMode::Change_BabaPos()
{
	for (ABabaBase*& ChangeBabas : Change_Baba) {
		ChangeBabas->ChangeTile(Baba_Actors);
	}
	Change_Baba.clear();
}

void APlayGameMode::BabaInputCheck()
{
	if (false == IsAnykeyDown()) {
		return;
	}
	if (ContentsHelper::Time >= 1) {
		for (std::pair<const __int64, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			for (ABabaBase*& _BabaBase : BabaBase) {
				_BabaBase->IsChecked = false;
			}
		}
		if (true == IsDown('A'))
		{
			Key = 'A';
			CanInput = false;
		}

		else if (true == IsDown('D'))
		{
			Key = 'D';
			CanInput = false;
		}

		else if (true == IsDown('W'))
		{
			Key = 'W';
			CanInput = false;
		}

		else if (true == IsDown('S'))
		{
			Key = 'S';
			CanInput = false;
		}
		else if (true == IsDown('Z'))
		{
			Stack_Pop();
			Change_BabaPos();
			CanInput = false;
			return;
		}
		else {
			Key = '0';
		}

		bool CanActive = false;
		for (std::pair<const __int64, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			for (ABabaBase*& _BabaBase : BabaBase) {
				if (_BabaBase->IsChecked == true) {
					continue;
				}
				if (_BabaBase->MoveCheck() == false) {
					_BabaBase->CanMove = false;
					continue;
				}
				_BabaBase->CanMove = false;
				bool Temp = _BabaBase->BabaMoveCheck(Key, Change_Baba, Baba_Actors);
				CanActive = (CanActive || Temp);
			}
		}
		if (true == CanActive) {
			Baba_Input();
			Change_BabaPos();
		}
	}
}

void APlayGameMode::DebugMessageFunction()
{
	{
		std::string Msg = std::format("Change BABA : {}\n", std::to_string(Change_Baba.size()));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

}



