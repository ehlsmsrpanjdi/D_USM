#include "PreCompile.h"
#include "PlayGameMode.h"
#include "BabaBase.h"
#include "PlayBack.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Rock.h"
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

	Baba_Actors[Player->GetTile64()].push_back(Player);
	Player->SetBabaLocation(0, 2);
	std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
	Back->SetActorLocation({ 0.0f, 0.0f, 500.0f });
	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	Baba_Input();
}

void APlayGameMode::Baba_Input()
{
	if (ContentsHelper::Time >= 1) {
		if (true == IsDown('A'))
		{
			Key = 'A';
			Stack_Push(Key);
		}

		if (true == IsDown('D'))
		{
			Key = 'D';
			Stack_Push(Key);
		}

		if (true == IsDown('W'))
		{
			Key = 'W';
			Stack_Push(Key);
		}

		if (true == IsDown('S'))
		{
			Key = 'S';
			Stack_Push(Key);
		}
		if (true == IsDown('Z'))
		{
			Key = 'Z';
			Stack_Pop();
		}
	}
}

void APlayGameMode::Stack_Push(char _Key)
{
	Stack_Input.push(_Key);
	ContentsHelper::Time = 0.f;

		for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>> &Iter : Baba_Actors)
		{
			std::list<std::shared_ptr<ABabaBase>> &BabaBase = Iter.second;
			for (std::shared_ptr<ABabaBase> &_BabaBase : BabaBase) {
				_BabaBase->SetKey(_Key);
				_BabaBase->IndexPlus(_BabaBase->Info);
				_BabaBase->InfoUpdate();
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
		for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>> &Iter : Baba_Actors)
		{
			std::list<std::shared_ptr<ABabaBase>> &BabaBase = Iter.second;
			for (std::shared_ptr<ABabaBase> &_BabaBase : BabaBase) {
				_BabaBase->SetKey(Temp_Key);
				_BabaBase->IndexMinus(_BabaBase->Info);
				_BabaBase->InfoUpdate();
				_BabaBase->PopLerpMove();
			}
		}
	}
}

void APlayGameMode::Change_BabaPos()
{
	for (std::pair<const __int64, std::list<std::shared_ptr<ABabaBase>>> Iter : Baba_Actors)
	{
		std::list<std::shared_ptr<ABabaBase>> &BabaBase = Iter.second;
		for (std::shared_ptr<ABabaBase> &ChangeBabas : Change_Baba) {
			BabaBase.remove(ChangeBabas);
			Baba_Actors[ChangeBabas->GetTile64()].push_back(ChangeBabas);
		}
	}
}
