#pragma once
#include <EngineCore/Actor.h>
#include <stack>
#include "ContentsHelper.h"

struct float2D
{
	float x;
	float y;

	float2D operator*(const float& _Value) {
		float ResultX = x * _Value;
		float ResultY = y * _Value;
		return float2D{ ResultX,ResultY };
	}

	float2D operator+(const float2D& _Value) {
		float ResultX = x + _Value.x;
		float ResultY = y + _Value.y;
		return float2D{ ResultX,ResultY };
	}

	bool operator==(const float2D& _Value) {
		if (x == _Value.x && y == _Value.y) {
			return true;
		}
		else {
			return false;
		}
	}
};


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
	BabaState State;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LerpMove(float _DeltaTime);
	float2D Lerp(float _DeltaTime);

	void GoBack(float _DeltaTime);

	void Move(float _DeltaTime);


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



private:

	float4 Color;
	float2D Location2D{};
	float2D NextLocation2D{};
};

