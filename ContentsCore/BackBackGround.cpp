#include "PreCompile.h"
#include "BackBackGround.h"
#include <EngineCore/DefaultSceneComponent.h>


BackBackGround::BackBackGround()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(2.0f, true);
	Renderer->SetSprite("Back_Two.png");
	Renderer->SetOrder(-200);
}

BackBackGround::~BackBackGround()
{
}

void BackBackGround::BeginPlay()
{
	Super::BeginPlay();

}
void BackBackGround::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}
