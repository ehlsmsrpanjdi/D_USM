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
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	LRenderer->SetupAttachment(Root);
	RRenderer->SetupAttachment(Root);
	Renderer->SetupAttachment(Root);
	SetRoot(Root);

	LRenderer->SetAutoSize(1.0f, true);
	RRenderer->SetAutoSize(1.0f, true);
	Renderer->SetAutoSize(1.4f, true);
	LRenderer->SetScale(FVector(18, 36));
	RRenderer->SetScale(FVector(18, 36));
	SetActive(true);
}

StageBox::~StageBox()
{
}

void StageBox::SetNextStage(std::string_view _StageName)
{
	std::string Name = _StageName.data();

	Renderer->CreateAnimation(Name, Name + ".png" , std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->ChangeAnimation(Name);

	LRenderer->SetActive(false);
	RRenderer->SetActive(false);
	Renderer->SetActive(true);
	BoxInfo = BoxEnum::Map;
}

void StageBox::SetLine(bool _Right, bool _Up, bool _Left, bool _Down)
{
	int index = 0;
	if (_Right == true) {
		index += 1;
	}
	if (_Up == true) {
		index += 2;
	}
	if (_Left == true) {
		index += 4;
	}
	if (_Down == true) {
		index += 8;
	}
	Renderer->ChangeAnimation("Line" + std::to_string(index));
	LRenderer->SetActive(false);
	RRenderer->SetActive(false);
	BoxInfo = BoxEnum::Line;
}

void StageBox::RenderOn()
{
	for (StageBox* Box : NextStage) {
		Box->SetActive(true);
	}
}

void StageBox::AnimationInit()
{
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
	Renderer->CreateAnimation("Line0", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Line1", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Line2", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Line3", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Line4", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Line5", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Line6", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Line7", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Line8", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Line9", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Line10", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Line11", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Line12", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Line13", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Line14", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Line15", "Line.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
}

void StageBox::BeginPlay()
{
	Super::BeginPlay();


	RRenderer->SetMaterial("2DImage");
	LRenderer->SetMaterial("2DImage");
	Renderer->SetMaterial("2DImage");

	LRenderer->SetOrder(2);
	RRenderer->SetOrder(2);
	Renderer->SetOrder(2);
	LRenderer->AddPosition(FVector::Left * 8.f);
	RRenderer->AddPosition(FVector::Right * 8.f);
	AnimationInit();
}

void StageBox::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

}

void StageBox::SetStageNum(std::string_view _Num)
{
	StageName = _Num;
	NumRender();
	BoxInfo = BoxEnum::Stage;
}

void StageBox::NumRender()
{
	if (StageName._Equal("Line")) {
		return;
	}
	std::string LeftNum = StageName.substr(0, 1);
	std::string RightNum = StageName.substr(1, 1);
	LRenderer->ChangeAnimation(LeftNum);
	RRenderer->ChangeAnimation(RightNum);
	Renderer->SetActive(false);
}


