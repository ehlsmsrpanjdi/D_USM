#include "PreCompile.h"
#include "BackGroundCirCle.h"
#include <EngineCore/DefaultSceneComponent.h>


BackGroundCirCle::BackGroundCirCle()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5, true);
}

BackGroundCirCle::~BackGroundCirCle()
{
}

void BackGroundCirCle::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("circle.png");
	Renderer->SetOrder(100);
}

void BackGroundCirCle::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
}
