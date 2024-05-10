#include "PreCompile.h"
#include "TitleButton.h"
#include <EngineCore/DefaultSceneComponent.h>

TitleButton::TitleButton()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.0f, true);
}

TitleButton::~TitleButton()
{
}

void TitleButton::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("StartTheGameBtn.png");
}

void TitleButton::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
