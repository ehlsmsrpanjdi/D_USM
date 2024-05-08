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
}

JellyBackGround::~JellyBackGround()
{
}

void JellyBackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Back_One.png");
	Renderer->SetOrder(-100);
	Renderer->SetScale(FVector(33 * 32, 18 * 32));
}

void JellyBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
