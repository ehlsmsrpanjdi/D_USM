#include "PreCompile.h"
#include "PlayGameMode.h"
#include "BabaBase.h"
#include "PlayBack.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Rock.h"
#include "TileMap.h"
#include <iterator>

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

	Player->SetBabaLocation(0, 2, 'D');
	Baba_Actors[Player->GetTile64()].push_back(Player);

	Player = GetWorld()->SpawnActor<ABabaBase>("Player");
	Player->SetBabaLocation(4, 2, 'W');
	Baba_Actors[Player->GetTile64()].push_back(Player);


	std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
	Back->SetActorLocation({ 0.0f, 0.0f, 500.0f });
	TileMap::TileSet(10, 10);

	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	BabaInputCheck();
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

	for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>>& Iter : Baba_Actors)
	{
		std::list<std::shared_ptr<ABabaBase>>& BabaBase = Iter.second;
		for (std::shared_ptr<ABabaBase>& _BabaBase : BabaBase) {
			_BabaBase->SetKey(_Key);
			_BabaBase->LerpMove();
			Change_Baba.push_back(_BabaBase);
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
		for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>>& Iter : Baba_Actors)
		{
			std::list<std::shared_ptr<ABabaBase>>& BabaBase = Iter.second;
			for (std::shared_ptr<ABabaBase>& _BabaBase : BabaBase) {
				_BabaBase->SetKey(Temp_Key);
				_BabaBase->PopLerpMove();
			}
		}
	}
}

void APlayGameMode::Change_BabaPos()
{
	//for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>> Iter : Baba_Actors)
	//{
	//	std::list<std::shared_ptr<ABabaBase>>& BabaBase = Iter.second;
	//	for (std::shared_ptr<ABabaBase>& ChangeBabas : Change_Baba) {
	//		if(Baba_Actors.contains(ChangeBabas))
	//		Baba_Actors[ChangeBabas->GetPrevTile64()].remove(ChangeBabas);
	//		Baba_Actors[ChangeBabas->GetTile64()].push_back(ChangeBabas);
	//	}
	//}
	


}

void APlayGameMode::BabaInputCheck()
{
	if (false == IsAnykeyDown()) {
		return;
	}
	if (ContentsHelper::Time >= 1) {
		if (true == IsDown('A'))
		{
			Key = 'A';
		}

		else if (true == IsDown('D'))
		{
			Key = 'D';
		}

		else if (true == IsDown('W'))
		{
			Key = 'W';
		}

		else if (true == IsDown('S'))
		{
			Key = 'S';
		}
		else if (true == IsDown('Z'))
		{
			Stack_Pop();
			Change_BabaPos();
			return;
		}
		else {
			Key = '0';
		}

		bool CanActive = false;
		for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>>& Iter : Baba_Actors)
		{
			std::list<std::shared_ptr<ABabaBase>>& BabaBase = Iter.second;
			for (std::shared_ptr<ABabaBase>& _BabaBase : BabaBase) {
				CanActive = (CanActive || _BabaBase->BabaActiveCheck(Key));
			}
		}
		if (true == CanActive) {
			Baba_Input();
			Change_BabaPos();
		}
	}
}


