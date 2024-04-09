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

	Actors.push_back(Player);
	Actors.push_back(Rock);

	std::shared_ptr<APlayBack> Back = GetWorld()->SpawnActor<APlayBack>("PlayBack");
	Back->SetActorLocation({ 0.0f, 0.0f, 500.0f });
	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	if (ContentsHelper::Time >= MoveTime) {
		IsInput = false;
	}
	ActorsMove();
}

void APlayGameMode::Input()
{
	++Count;
	IsInput = true;
	ContentsHelper::Time = 0.f;
}

void APlayGameMode::ActorsMove()
{
	if (IsInput == false) {
		if (true == IsDown('A'))
		{
			Key = 'A';
			Input();
		}

		if (true == IsDown('D'))
		{
			Key = 'D';
			Input();
		}

		if (true == IsDown('W'))
		{
			Key = 'W';
			Input();
		}

		if (true == IsDown('S'))
		{
			Key = 'S';
			Input();
		}
		if (true == IsDown('Z'))
		{
			if (Count == 0) {
				return;
			}
			Key = 'Z';
			Count--;
			IsInput = true;
			ContentsHelper::Time = 0.f;
		}
	}
	if (Key != '0') {

		for (auto Actor : Actors) {
			if (Actor->State.IsMove == true || Key == 'Z') {
				Actor->Stack_Input.push(Key);
			}
			else if (Actor->State.IsMove == false) {
				Actor->Stack_Input.push('0');
			}
		}
	}
	Key = '0';
}
