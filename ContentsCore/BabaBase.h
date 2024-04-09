#pragma once
#include <EngineCore/Actor.h>
#include <stack>
#include <EngineCore/StateManager.h>
#include "ContentsHelper.h"

// Ό³Έν :
class USpriteRenderer;
class ABabaBase : public AActor
{
	GENERATED_BODY(AActor)

public:
	// constrcuter destructer
	ABabaBase();
	~ABabaBase();

	// delete Function
	ABabaBase(const ABabaBase& _Other) = delete;
	ABabaBase(ABabaBase&& _Other) noexcept = delete;
	ABabaBase& operator=(const ABabaBase& _Other) = delete;
	ABabaBase& operator=(ABabaBase&& _Other) noexcept = delete;

	std::stack<char> Stack_Input;
	UStateManager FSM_State;
	BabaState State;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LerpMove(float _DeltaTime);
	float2D Lerp(float _DeltaTime);

	void GoBack(float _DeltaTime);

	void Push_Stack(float _DeltaTime);


	inline void SetNextLocation2D(float _x, float _y) {
		NextLocation2D = { _x,_y };
	}

	inline void SetLocation2D(float _x, float _y) {
		Location2D = { _x,_y };
	}

	inline float4 Location2Dto4D() {
		return float4(Location2D.x, Location2D.y);
	}

	inline void AddNextLocation2D(float _x, float _y) {
		Stack_Location.push(Location2D);
		float x = Location2D.x + _x;
		float y = Location2D.y + _y;
		IsMoving = true;
		SetNextLocation2D(x, y);
	}

	void SetActorlocation2D(float2D _Value) {
		SetActorLocation(float4{ _Value.x, _Value.y });
	}


	float MoveCoolTime = 0.f;
	bool IsMoving = false;
	bool IsInput = false;
	std::stack<float2D> Stack_Location;
	USpriteRenderer* Renderer;


	///////////////////////// BabaState
	void StateInit();

	void Die(float _DeltaTime);

	void Idle(float _DeltaTime);
	void IdleStart();

	void MoveStart();
	void Move(float _DeltaTime);
	void MoveEnd();


private:

	float4 Color;
	float2D Location2D{};
	float2D NextLocation2D{};
};

