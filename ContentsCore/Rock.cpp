#include "PreCompile.h"
#include "Rock.h"
#include <EngineCore/SpriteRenderer.h>

ARock::ARock()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
}

ARock::~ARock()
{
}

void ARock::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetSprite("CharIdle0.png");
	SetActorScale3D(FVector(200.0f, 200.0f, 100.0f));
}

void ARock::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	if (true == IsDown('E'))
	{
		State.IsMove = true;
	}

	if (true == IsDown('R'))
	{
		State.IsMove = false;
	}
	Move(_DeltaTime);
	LerpMove(_DeltaTime);
}