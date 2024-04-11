#pragma once
#include <EngineCore/Actor.h>
#include <stack>
#include <EngineCore/StateManager.h>
#include "ContentsHelper.h"

// Ό³Έν :

struct BabaInfo {
	int AnimationIndex = 1;
	BabaObject Who = BabaObject::Baba;
};

class APlayGameMode;
class USpriteRenderer;
class ABabaBase : public AActor
{
	GENERATED_BODY(AActor)
	friend APlayGameMode;
public:
	// constrcuter destructer
	ABabaBase();
	~ABabaBase();

	// delete Function
	ABabaBase(const ABabaBase& _Other) = delete;
	ABabaBase(ABabaBase&& _Other) noexcept = delete;
	ABabaBase& operator=(const ABabaBase& _Other) = delete;
	ABabaBase& operator=(ABabaBase&& _Other) noexcept = delete;

	char BabaInput = '0';
	UStateManager FSM_State;
	BabaState State;
	BabaInfo Info;
protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LerpMove();
	void PopLerpMove();
	float2D Lerp(float _DeltaTime);

	inline void SetNextLocation2D(float _x, float _y) {
		NextLocation2D = { _x,_y };
	}

	inline void SetLocation2D(float _x, float _y) {
		Location2D = { _x,_y };
	}

	inline float4 Location2Dto4D() {
		return float4(Location2D.x, Location2D.y);
	}

	void SetActorlocation2D(float2D _Value) {
		SetActorLocation(float4{ _Value.x, _Value.y });
	}

	USpriteRenderer* Renderer;

	void IndexPlus(BabaInfo& _Info);
	void IndexMinus(BabaInfo& _Info);
	void InfoUpdate();
	std::string InputToButton(char _Input);


private:

	float4 Color;
	float2D Location2D{};
	float2D NextLocation2D{};
};

