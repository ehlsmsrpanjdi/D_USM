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
	Renderer->CreateAnimation("MoveOn", "Move.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("PullOn", "Pull.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("PushOn", "Push.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("StopOn", "Stop.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("DefeatOn", "Defeat.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("HotOn", "Hot.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("SinkOn", "Sink.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("YouOn", "You.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("WinOn", "Win.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("MeltOn", "Melt.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("OpenOn", "Open.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("ShutOn", "Shut.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{2, 5, 8});

	Renderer->CreateAnimation("Move", "Move.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Pull", "Pull.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Push", "Push.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Stop", "Stop.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Defeat", "Defeat.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Hot", "Hot.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Sink", "Sink.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("You", "You.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Win", "Win.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Melt", "Melt.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Open", "Open.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->CreateAnimation("Shut", "Shut.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});



	Renderer->ChangeAnimation("push");
	IsOn = false;
}

void ActiveWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
	SetActiveAnimation();
}

void ActiveWord::SetActiveAnimation()
{
	std::string StrOn = "";
	if (IsOn == true) {
		StrOn = "On";
	}
	if (ActiveName.IsDefeat) {
		Renderer->ChangeAnimation("defeat" + StrOn);
	}
	else if (ActiveName.IsFloat) {
		Renderer->ChangeAnimation("float" + StrOn);
	}
	else if (ActiveName.IsHot) {
		Renderer->ChangeAnimation("hot" + StrOn);
	}
	else if (ActiveName.IsMelt) {
		Renderer->ChangeAnimation("melt" + StrOn);
	}
	else if (ActiveName.IsMove && !ActiveName.IsYou) {
		Renderer->ChangeAnimation("move" + StrOn);
	}
	else if (ActiveName.IsPull) {
		Renderer->ChangeAnimation("pull" + StrOn);
	}
	else if (ActiveName.IsPush) {
		Renderer->ChangeAnimation("push" + StrOn);
	}
	else if (ActiveName.IsSink) {
		Renderer->ChangeAnimation("sink" + StrOn);
	}
	else if (ActiveName.IsStop) {
		Renderer->ChangeAnimation("stop" + StrOn);
	}
	else if (ActiveName.IsWin) {
		Renderer->ChangeAnimation("win" + StrOn);
	}
	else if (ActiveName.IsYou) {
		Renderer->ChangeAnimation("You" + StrOn);
	}
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
	else if (_Str._Equal("MELT")) {
		Renderer->ChangeAnimation("MELT");
	}
	else if (_Str._Equal("SHUT")) {
		Renderer->ChangeAnimation("SHUT");
	}
	else if (_Str._Equal("OPEN")) {
		Renderer->ChangeAnimation("OPEN");
	}
	else {
		MsgBoxAssert("ActiveName에 이상한거넣었음");
	}
}
