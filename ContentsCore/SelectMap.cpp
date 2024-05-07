#include "PreCompile.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "SelectMap.h"

SelectMap::SelectMap()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");

	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5f, true);
}

SelectMap::~SelectMap()
{
}

void SelectMap::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetMaterial("2DImage");
	Renderer->CreateAnimation("SelectMap", "SelectMap_background.png");
	Renderer->ChangeAnimation("SelectMap");
	SetOrder(-100);
}

void SelectMap::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
