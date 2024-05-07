#include "PreCompile.h"
#include "BackGround.h"
#include <EngineCore/DefaultSceneComponent.h>

float4 BackGround::BackgroundSize = {};

BackGround::BackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1, true);
	//BackgroundSize = Renderer->();
	int a = 0;
}

BackGround::~BackGround()
{
}

void BackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Back_One.png");
	Renderer->SetOrder(-100);
}

void BackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
