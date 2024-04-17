#include "PreCompile.h"
#include "NameWord.h"
#include <EngineCore/Actor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>


NameWord::NameWord()
{
}

NameWord::~NameWord()
{
}

void NameWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");
	Renderer->SetSprite("Wall.png");
}

void NameWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}
