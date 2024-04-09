#include "PreCompile.h"
#include "BabaBase.h"
#include <EngineCore/SpriteRenderer.h>

void ABabaBase::StateInit() {
	FSM_State.CreateState("Die");
	FSM_State.CreateState("Idle");
	FSM_State.CreateState("Run");
}

void ABabaBase::Die(float _DeltaTime)
{
}

void ABabaBase::Idle(float _DeltaTime)
{
	if
}

void ABabaBase::IdleStart()
{
	Renderer->ChangeAnimation("Idle");
}

void ABabaBase::MoveStart()
{
	Renderer->ChangeAnimation("Move");
}

void ABabaBase::Move(float _DeltaTime)
{
	
}

void ABabaBase::MoveEnd()
{
	Renderer->ChangeAnimation("Idle");
}



