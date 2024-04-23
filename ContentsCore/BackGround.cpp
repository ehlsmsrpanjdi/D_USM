#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/DefaultSceneComponent.h>


BackGround::BackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5, true);
}

BackGround::~BackGround()
{
}

void BackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("black.png");
	Renderer->SetOrder(100);
}

void BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
