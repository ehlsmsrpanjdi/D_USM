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
	Renderer->CreateAnimation("BabaName","Baba.Png");
	Renderer->CreateAnimation("WallName", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("LavaName", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("WaterName", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("GrassName", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("RockName", "Rock.Png");
	Renderer->CreateAnimation("SkullName", "Skull.Png");
	Renderer->CreateAnimation("FlagName", "Flag.Png");
	Renderer->ChangeAnimation("WallName");
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
	case BabaState::IsWall:
		Renderer->ChangeAnimation("WallName");
		break;
	case BabaState::IsRock:
		Renderer->ChangeAnimation("RockName");
		break;
	case BabaState::IsFlag:
		Renderer->ChangeAnimation("FlagName");
		break;
	case BabaState::IsSkull:
		Renderer->ChangeAnimation("SkullName");
		break;
	case BabaState::IsWater:
		Renderer->ChangeAnimation("WaterName");
		break;
	case BabaState::IsLava:
		Renderer->ChangeAnimation("LavaName");
		break;
	case BabaState::IsGrass:
		Renderer->ChangeAnimation("GrassName");
		break;
	default:
		break;
	}
}
