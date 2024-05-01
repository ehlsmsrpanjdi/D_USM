#include "PreCompile.h"
#include "Dust.h"
#include <EngineCore/DefaultSceneComponent.h>
#include "ContentsHelper.h"


Dust::Dust()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.f ,true);
}

Dust::~Dust()
{
}

void Dust::SetReleaseLocation(char _Input)
{
	ReleaseLocation = _Input;
}

void Dust::SetColor(BabaState _State)
{
	float4 Color;
	switch (_State)
	{
	case BabaState::IsWall:
		Color = ColorChange(0, 51, 51);
		Renderer->SetMulColor(Color);
		break;
	case BabaState::IsRock:
		Color = ColorChange(153,102,51);
		Renderer->SetMulColor(Color);
		break;
	case BabaState::IsFlag:
		Color = ColorChange(255,255,0);
		Renderer->SetMulColor(Color);
		break;
	case BabaState::IsSkull:
		Color = ColorChange(153,0,0);
		Renderer->SetMulColor(Color);
		break;
	case BabaState::IsWater:
		Color = ColorChange(0,204,255);
		Renderer->SetMulColor(Color);
		break;
	case BabaState::IsLava:
		Color = ColorChange(255,102,0);
		Renderer->SetMulColor(Color);
		break;
	default:
		break;
	}
}

void Dust::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("Dust0.png");
	Renderer->SetOrder(100);
	Scale = Renderer->GetWorldScale();
}

void Dust::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ReleaseTime += _DeltaTime * 0.1f;
	FVector MinusScale = Scale * ReleaseTime * 0.1f;
	Scale = Scale - MinusScale;
	Renderer->SetScale(Scale);
	TotalTime += _DeltaTime;
	SetInputBaseLocation(MinusScale);
	if (TotalTime >= 1) {
		Destroy();
	}
}

void Dust::SetInputBaseLocation(FVector _Scale)
{
	switch (ReleaseLocation)
	{
	case 'W':
		Renderer->AddPosition(FVector::Down * _Scale);
		break;
	case 'A':
		Renderer->AddPosition((FVector::Right * _Scale) + (FVector::Down * 0.5f * _Scale));
		break;
	case 'S':
		Renderer->AddPosition(FVector::Up * _Scale);
		break;
	case 'D':
		Renderer->AddPosition((FVector::Left * _Scale )+ (FVector::Down * 0.5f * _Scale));
		break;
	default:
		break;
	}
}
