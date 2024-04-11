#include "PreCompile.h"
#include "PlayGameMode.h"
#include "BabaBase.h"
#include "PlayBack.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "Rock.h"

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

	std::shared_ptr<ARock> Rock = GetWorld()->SpawnActor<ARock>("Rock");

	Baba_Actors.push_back(Player);
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
	for (std::shared_ptr<ABabaBase> _BabaBase : Baba_Actors) {
		_BabaBase->BabaInput = Key;
		_BabaBase->IndexPlus(_BabaBase->Info);
		_BabaBase->InfoUpdate();
		_BabaBase->LerpMove();
	}
}
void APlayGameMode::Stack_Pop()
{
	char Temp_Key;
	if (Stack_Input.empty() != true) {
		Temp_Key = Stack_Input.top();
		Stack_Input.pop();
		ContentsHelper::Time = 0.f;
		for (std::shared_ptr<ABabaBase> _BabaBase : Baba_Actors) {
			_BabaBase->BabaInput = Temp_Key;
			_BabaBase->IndexMinus(_BabaBase->Info);
			_BabaBase->InfoUpdate();
			_BabaBase->PopLerpMove();
		}
	}
}
