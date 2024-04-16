#include "PreCompile.h"
#include "Word.h"
#include <EngineCore/Actor.h>


AWord::AWord()
{
}

AWord::~AWord()
{
}

void AWord::BeginPlay()
{
	Super::BeginPlay();
}

void AWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void AWord::WorldInit()
{
	AState = { false, true, true };
}

// isbaba, ismove, ispush
