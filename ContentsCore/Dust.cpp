#include "PreCompile.h"
#include "Dust.h"
#include <EngineCore/DefaultSceneComponent.h>


Dust::Dust()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5, true);
}

Dust::~Dust()
{
}

void Dust::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Dust0.png");
	Renderer->SetOrder(100);
}

void Dust::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
