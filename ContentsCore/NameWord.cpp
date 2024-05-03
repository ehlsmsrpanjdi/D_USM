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
	Renderer->CreateAnimation("WallNameOn", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 19, 37 });

	Renderer->CreateAnimation("IceName", "Ice.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("IceNameOn", "Ice.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 19, 37 });

	Renderer->CreateAnimation("LavaName", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("LavaNameOn", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 19, 37 });

	Renderer->CreateAnimation("WaterName", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("WaterNameOn", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 19, 37 });

	Renderer->CreateAnimation("GrassName", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 18, 36 });
	Renderer->CreateAnimation("GrassNameOn", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 19, 37 });

	Renderer->CreateAnimation("RockName", "Rock.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 2, 4 });
	Renderer->CreateAnimation("SkullName", "Skull.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 0, 2, 4 });
	Renderer->CreateAnimation("FlagName", "Flag.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 1, 4, 7 });

	Renderer->CreateAnimation("RockNameOn", "Rock.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{1, 3, 5 });
	Renderer->CreateAnimation("SkullNameOn", "Skull.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{1,3,5});
	Renderer->CreateAnimation("FlagNameOn", "Flag.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});

	Renderer->ChangeAnimation("WallName");
}

void NameWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
	NameWordChangeAnimation();
}

void NameWord::NameWordChangeAnimation()
{
	std::string StrOn = "";
	if (IsOn == true) {
		StrOn = "On";
	}
	switch (WordInfo)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Renderer->ChangeAnimation("BabaName");
		break;
	case BabaState::IsWall:
		Renderer->ChangeAnimation("WallName" + StrOn);
		break;
	case BabaState::IsRock:
		Renderer->ChangeAnimation("RockName" + StrOn);
		break;
	case BabaState::IsFlag:
		Renderer->ChangeAnimation("FlagName" + StrOn);
		break;
	case BabaState::IsSkull:
		Renderer->ChangeAnimation("SkullName" + StrOn);
		break;
	case BabaState::IsWater:
		Renderer->ChangeAnimation("WaterName" + StrOn);
		break;
	case BabaState::IsLava:
		Renderer->ChangeAnimation("LavaName" + StrOn);
		break;
	case BabaState::IsGrass:
		Renderer->ChangeAnimation("GrassName" + StrOn);
		break;
	case BabaState::IsIce:
		Renderer->ChangeAnimation("IceName" + StrOn);
		break;
	default:
		break;
	}
}
