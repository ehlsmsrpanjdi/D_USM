#include "PreCompile.h"
#include "Bababase.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>

ABabaBase::ABabaBase()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	InputOn();
}

ABabaBase::~ABabaBase()
{
}

void ABabaBase::BeginPlay()
{
	Super::BeginPlay();

	SetActorScale3D(FVector(200.0f, 200.0f, 100.0f));
	State.IsMove = true;
	// 내부에서 샘플러도 같이 찾을
	Renderer->SetSprite("CharIdle0.png");
	float4 Location4D = GetActorLocation();
	Location2D.x = Location4D.X;
	Location2D.y = Location4D.Y;

	Renderer->CreateAnimation("Die", "Die");
	Renderer->CreateAnimation("Idle", "Idle");
	Renderer->CreateAnimation("Move", "Move");

	StateInit();
	FSM_State.ChangeState("Idle");

}

void ABabaBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	
	//Push_Stack(_DeltaTime);
	//LerpMove(_DeltaTime);
	FSM_State.Update(_DeltaTime);
}

void ABabaBase::LerpMove(float _DeltaTime)
{
	SetActorlocation2D(Lerp(MoveCoolTime));
}

float2D ABabaBase::Lerp(float _DeltaTime)
{
	if (ContentsHelper::Time < MoveTime && IsMoving == true) {
		return Location2D * (MoveTime - ContentsHelper::Time) + NextLocation2D * (ContentsHelper::Time);
	}
	else if (IsMoving == true) {
		IsMoving = false;
		Location2D = NextLocation2D;
		return Location2D;
	}
	else {
		return Location2D;
	}
}

void ABabaBase::GoBack(float _DeltaTime)
{
	if (Stack_Location.empty() == true) {
		return;
	}
	float2D Temp = Stack_Location.top();
	Stack_Location.pop();
	SetNextLocation2D(Temp.x, Temp.y);
	IsMoving = true;
}


void ABabaBase::Push_Stack(float _DeltaTime)
{
	if (ContentsHelper::Time <= MoveTime && Stack_Input.empty() != true) {
		char Key = Stack_Input.top();
		IsMoving = true;
		Stack_Input.pop();
		switch (Key) {
		case 'A':
			AddNextLocation2D(-50, 0);
			break;
		case 'D':
			AddNextLocation2D(50, 0);
			break;
		case 'S':
			AddNextLocation2D(0, -50);
			break;
		case 'W':
			AddNextLocation2D(0, 50);
			break;
		case 'Z':
			GoBack(_DeltaTime);
			break;
		default:
			AddNextLocation2D(0, 0);
			break;
		}
	}
}

