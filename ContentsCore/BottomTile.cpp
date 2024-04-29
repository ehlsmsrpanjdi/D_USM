#include "PreCompile.h"
#include "BottomTile.h"
#include <EngineCore/DefaultSceneComponent.h>


BottomTile::BottomTile()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5f, true);
	Renderer->CreateAnimation("Tile", "Tile.png");
	Renderer->ChangeAnimation("Tile");
}

BottomTile::~BottomTile()
{
}

void BottomTile::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(-1);
}

void BottomTile::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
}
