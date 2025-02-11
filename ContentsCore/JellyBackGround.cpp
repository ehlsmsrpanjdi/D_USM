#include "PreCompile.h"
#include "JellyBackGround.h"
#include <EngineCore/DefaultSceneComponent.h>


JellyBackGround::JellyBackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1, true);
	Renderer->SetSprite("Back_Two.png");
}

JellyBackGround::~JellyBackGround()
{
}

void JellyBackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(-100);
}

void JellyBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
