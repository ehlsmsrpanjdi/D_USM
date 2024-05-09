#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "JellySelectMap.h"


JellySelectMap::JellySelectMap()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.f, true);
	Renderer->SetMaterial("2DImage");
	Renderer->SetSprite("Back_Jelly.png");
}

JellySelectMap::~JellySelectMap()
{
}

void JellySelectMap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetOrder(-100);

}

void JellySelectMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
