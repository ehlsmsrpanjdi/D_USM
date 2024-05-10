#include "PreCompile.h"
#include "TitleGameMode.h"
#include "BackGround.h"
#include "BackBackGround.h"
#include "Text.h"
#include "TitleButton.h"
#include "ContentsHelper.h"
#include "FadeOUTEffect.h"
#include "FadeINEffect.h"


TitleGameMode::TitleGameMode()
{
}

TitleGameMode::~TitleGameMode()
{
}

std::shared_ptr<Text> TitleGameMode::SpawnText(std::string_view _TextName)
{
	std::shared_ptr<Text> Tex = GetWorld()->SpawnActor<Text>("A");
	Tex->TextChange(_TextName);
	return Tex;
}

void TitleGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0.f, 0.0f, -100.0f));
	GetWorld()->SpawnActor<BackGround>("a");

	GetWorld()->SpawnActor<BackBackGround>("A");

	ContentsHelper::WordInit();
	InputOn();

	std::shared_ptr<Text> Tex = SpawnText("B");
	Tex->AddActorLocation(FVector(-200, 100));
	Tex->MulColor(FVector::Red);
	Tex = SpawnText("A");
	Tex->MulColor(FVector::Red);
	Tex->AddActorLocation(FVector(-160, 100));
	Tex = SpawnText("B");
	Tex->MulColor(FVector::Red);
	Tex->AddActorLocation(FVector(-120, 100));
	Tex = SpawnText("A");
	Tex->MulColor(FVector::Red);
	Tex->AddActorLocation(FVector(-80, 100));

	Tex = SpawnText("I");
	Tex->AddActorLocation(FVector(0, 100));
	Tex = SpawnText("S");
	Tex->AddActorLocation(FVector(40, 100));

	Tex = SpawnText("Y");
	Tex->AddActorLocation(FVector(120, 100));
	Tex->MulColor(FVector::Red);
	Tex = SpawnText("O");
	Tex->AddActorLocation(FVector(160, 100));
	Tex->MulColor(FVector::Red);
	Tex = SpawnText("U");
	Tex->AddActorLocation(FVector(200, 100));
	Tex->MulColor(FVector::Red);

	Tex = SpawnText("Baba");
	Tex->AddActorLocation(FVector(-350, 0));
	Selector = Tex.get();

	GetWorld()->SpawnActor<TitleButton>("Title");
	std::shared_ptr<TitleButton> Button = GetWorld()->SpawnActor<TitleButton>("Title");
	Button->AddActorLocation(FVector::Down * 100);
	Button->SetNum(3);


}

void TitleGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (IsDown(VK_DOWN) || IsDown('S')) {
		if (Select == 0) {
			++Select;
			Selector->AddActorLocation(FVector::Down * 100);
		}
	}
	if (IsDown(VK_UP) || IsDown('W')) {
		if (Select == 1) {
			--Select;
			Selector->AddActorLocation(FVector::Up * 100);
		}
	}

	if (IsDown(VK_RETURN)) {
		if (Select == 0) {
			Effect = GetWorld()->GetLastTarget()->AddEffect<FadeOUTEffect>().get();
			FadeOn = true;
			InputOff();
		}
		else if (Select == 1) {
			GEngine->EngineWindow.Off();
		}
	}

	if (FadeOn == true) {
		FadeTime += _DeltaTime;
		if (FadeTime >= 2) {
			Effect->ResetTime();
			Effect->EffectOff();
			GEngine->ChangeLevel("SelectGameLevel");
		}
	}

}
