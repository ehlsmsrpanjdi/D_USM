#include "PreCompile.h"
#include "ActiveWord.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ActiveWord::ActiveWord()
{
}

ActiveWord::~ActiveWord()
{
}

void ActiveWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");		
	Renderer->CreateAnimation("Baba", "Baba.Png");
	Renderer->CreateAnimation("Move", "Move.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Pull", "Pull.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Push", "Push.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Stop", "Stop.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Defeat", "Defeat.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Hot", "Hot.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("Sink", "Sink.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->CreateAnimation("You", "You.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});

	Renderer->ChangeAnimation("push");
}

void ActiveWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}

void ActiveWord::SetAnimation(std::string_view _Str)
{
	if (_Str._Equal("PUSH")) {
		Renderer->ChangeAnimation("Push");
	}
	else if (_Str._Equal("MOVE")) {
		Renderer->ChangeAnimation("MOVE");
	}
	else if (_Str._Equal("STOP")) {
		Renderer->ChangeAnimation("STOP");
	}
	else if (_Str._Equal("PULL")) {
		Renderer->ChangeAnimation("PULL");
	}
	else if (_Str._Equal("HOT")) {
		Renderer->ChangeAnimation("HOT");
	}
	else if (_Str._Equal("FLOAT")) {
		Renderer->ChangeAnimation("FLOAT");
	}
	else if (_Str._Equal("SINK")) {
		Renderer->ChangeAnimation("SINK");
	}
	else if (_Str._Equal("WIN")) {
		Renderer->ChangeAnimation("WIN");
	}
	else if (_Str._Equal("DEFEAT")) {
		Renderer->ChangeAnimation("DEFEAT");
	}
	else if (_Str._Equal("YOU")) {
		Renderer->ChangeAnimation("YOU");
	}
	else {
		MsgBoxAssert("ActiveName에 이상한거넣었음");
	}
}
