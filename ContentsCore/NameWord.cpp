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
	Renderer->CreateAnimation("BabaName","Baba.Png");
	Renderer->CreateAnimation("WallName", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
		
}

void NameWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}

void NameWord::NameWordChangeAnimation()
{
	switch (WordInfo)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Renderer->ChangeAnimation("BabaName");
		break;
	case BabaState::IsRock:
		Renderer->ChangeAnimation("WallName");
		break;
	default:
		break;
	}
}
