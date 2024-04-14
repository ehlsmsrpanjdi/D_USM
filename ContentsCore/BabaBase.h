#pragma once
#include <EngineCore/Actor.h>
#include <stack>
#include <EngineCore/StateManager.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineCore.h>


// Ό³Έν :

struct BabaInfo {
	int AnimationIndex = 1;
	BabaObject Who = BabaObject::Baba;
	TilePoint Tile = {};
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
	char StartInput = '0';
	BabaInfo Info;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void LerpMove();
	void PopLerpMove();
	float2D Lerp(float _DeltaTime);

	inline void SetNextLocation2D(float2D _2D) {
		SetNextLocation2D(_2D.x, _2D.y);
	}

	inline void SetNextLocation2D(float _x, float _y) {
		NextLocation2D = { _x,_y };
	}

	inline void SetLocation2D(float _x, float _y) {
		Location2D = { _x,_y };
	}

	inline void SetLocation2D(float2D _2D) {
		SetLocation2D(_2D.x, _2D.y);
	}

	inline float4 Location2Dto4D() {
		return float4(Location2D.x, Location2D.y);
	}

	inline float2D TileReturn() {
		float X = Info.Tile.X * MoveLength;
		float Y = Info.Tile.Y * MoveLength;
		return float2D{ X,Y };
	}

	void SetBabaLocation(int _X, int _Y, char _Input = 'D') {
		Info.Tile.X = static_cast<int>(_X);
		Info.Tile.Y = static_cast<int>(_Y);
		BabaInput = _Input;
		StartInput = _Input;
		InfoUpdate();
		SetLocation2D(TileReturn());
		SetNextLocation2D(TileReturn());
	}

	void SetKey(char _Key) {
		BabaInput = _Key;
	}

	TilePoint GetTile() {
		return Info.Tile;
	}

	__int64 GetTile64() {
		return Info.Tile.Location;
	}

	TilePoint GetPrevTile() {
		return PrevTile;
	}

	__int64 GetPrevTile64() {
		return PrevTile.Location;
	}

	void SetActorlocation2D(float2D _Value) {
		SetActorLocation(float4{ _Value.x, _Value.y });
	}

	USpriteRenderer* Renderer;
	void IndexPlus(BabaInfo& _Info);
	void IndexMinus(BabaInfo& _Info);
	void InfoUpdate();
	std::string InputToButton(char _Input);

	bool BabaActiveCheck(char _Input);

	void DebugMessageFunction();

	void ChangeTile(std::map<__int64, std::list<ABabaBase*>>& _Baba_Actors);


private:
	std::stack<bool> Move_Stack;
	float4 Color;
	float2D Location2D{};
	float2D NextLocation2D{};
	TilePoint PrevTile;
};

