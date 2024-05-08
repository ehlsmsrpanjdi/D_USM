#include "PreCompile.h"
#include "BackBackGround.h"
#include <EngineCore/DefaultSceneComponent.h>


BackBackGround::BackBackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1, true);
}

BackBackGround::~BackBackGround()
{
}

void BackBackGround::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Back_One.png");
	Renderer->SetOrder(-200);

}
void BackBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
