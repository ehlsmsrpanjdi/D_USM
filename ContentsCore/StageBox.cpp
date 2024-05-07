#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "StageBox.h"

StageBox::StageBox()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	LRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	RRenderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	LRenderer->SetupAttachment(Root);
	RRenderer->SetupAttachment(Root);
	SetRoot(Root);

	LRenderer->SetAutoSize(1.0f, true);
	RRenderer->SetAutoSize(1.0f, true);
	LRenderer->SetScale(FVector(18, 36));
	RRenderer->SetScale(FVector(18, 36));
}

StageBox::~StageBox()
{
}


void StageBox::BeginPlay()
{
	Super::BeginPlay();


	RRenderer->SetMaterial("2DImage");
	LRenderer->SetMaterial("2DImage");

	LRenderer->SetOrder(2);
	RRenderer->SetOrder(2);
	LRenderer->AddPosition(FVector::Left * 8.f);
	RRenderer->AddPosition(FVector::Right * 8.f);


	LRenderer->CreateAnimation("0", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 0 });
	LRenderer->CreateAnimation("1", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 1 });
	LRenderer->CreateAnimation("2", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 2 });
	LRenderer->CreateAnimation("3", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 3 });
	LRenderer->CreateAnimation("4", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 4 });
	LRenderer->CreateAnimation("5", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 5 });
	LRenderer->CreateAnimation("6", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 6 });
	LRenderer->CreateAnimation("7", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 7 });
	LRenderer->CreateAnimation("8", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 8 });
	LRenderer->CreateAnimation("9 ", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 9 });

	RRenderer->CreateAnimation("0", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 0 });
	RRenderer->CreateAnimation("1", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 1 });
	RRenderer->CreateAnimation("2", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 2 });
	RRenderer->CreateAnimation("3", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 3 });
	RRenderer->CreateAnimation("4", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 4 });
	RRenderer->CreateAnimation("5", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 5 });
	RRenderer->CreateAnimation("6", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 6 });
	RRenderer->CreateAnimation("7", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 7 });
	RRenderer->CreateAnimation("8", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 8 });
	RRenderer->CreateAnimation("9", "NumberFont.png", std::vector<float>{ 0.1f }, std::vector<int>{ 9 });
}

void StageBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void StageBox::SetStageNum(std::string_view _Num)
{
	StageName = _Num;
	NumRender();
}

void StageBox::NumRender()
{
	std::string LeftNum = StageName.substr(0, 1);
	std::string RightNum = StageName.substr(1, 1);
	LRenderer->ChangeAnimation(LeftNum);
	RRenderer->ChangeAnimation(RightNum);

}


