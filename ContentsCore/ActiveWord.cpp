#include "PreCompile.h"
#include "ActiveWord.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

ActiveWord::ActiveWord()
{
}

ActiveWord::~ActiveWord()
{
}

void ActiveWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");
	Renderer->SetSprite("Push.png");
}

void ActiveWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}
