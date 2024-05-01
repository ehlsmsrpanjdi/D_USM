#pragma once
#include <EngineCore/Actor.h>
#include <stack>
#include <EngineCore/StateManager.h>
#include "ContentsHelper.h"
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineCore.h>

// 설명 :

struct BabaInfo {
	int AnimationIndex = 1;
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

	BabaState BState = BabaState::IsBaba;
	//ActiveState AState = {false,false,false};

	// delete Function
	ABabaBase(const ABabaBase& _Other) = delete;
	ABabaBase(ABabaBase&& _Other) noexcept = delete;
	ABabaBase& operator=(const ABabaBase& _Other) = delete;
	ABabaBase& operator=(ABabaBase&& _Other) noexcept = delete;

	char BabaInput = '0';
	char StartInput = '0';
	BabaInfo Info;

	//enum class BabaState {
	//	IsNone = 0,
	//	IsBaba,
	//	IsRock,
	//	IsWord,
	//	IsActive,
	//	IsIs,			BState로 현재 바바가 무슨 오브젝트인지 알아낸다.
	//};				Rock, Wall, Lava 같은 상태이면 그냥 그 상태 그대로 쓰면됨
	//					하지만 단어거나 Active면 조금 다른 방식으로 가져온다
	//					Active 동작하는 단어이면 Active로 Set해줘야한다.
	//					Is는 Is이다.					
	//					Word는 어떤 Actor의 이름을 표현한다.
	//
	//					ActiveState로 어떠한 State를 Set해주거나 어떠한 상태인지 말해준다.
	//					Word이면 WordInfo로 확인한다. WordInfo도 Bstate다
	//

	BabaState GetBstate() {
		return BState;
	}

	bool IsOn = false;

	bool GetDead() {
		return Dead;
	}

	void SetDead(bool _Dead) {
		Dead = _Dead;
	}

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
		SetActorlocation2D(TileReturn());
		SetNextLocation2D(TileReturn());
	}

	void SetBabaLocation(TilePoint _Tile, char _Input = 'D') {
		Info.Tile.X = static_cast<int>(_Tile.X);
		Info.Tile.Y = static_cast<int>(_Tile.Y);
		BabaInput = _Input;
		StartInput = _Input;
		InfoUpdate();
		SetLocation2D(TileReturn());
		SetActorlocation2D(TileReturn());
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

	bool BabaMapCheck(char _Input);

	//void DebugMessageFunction();

	void ChangeTile(std::map<TilePoint, std::list<ABabaBase*>>& _Baba_Actors);

	bool MoveCheck();
	bool PushCheck();
	bool StopCheck();
	void StateInit(BabaState _State);

	bool BabaMoveCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	bool BabaPushCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	bool BabaNextTileCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile);

	TilePoint KeyTileReturn(char _Input);
	void KeyTileSet(char _Input);
	void KeyTileSetReverse(char _Input);

	void BabaHelperUpdate();
	void BabaUpdate();
	void BabaUpdater();

	void Babachange();
	void RockChange();
	void FlagChange();
	void SkullChange();
	void WaterChange();
	void LavaChange();
	void WallChange();

	void RenderInit();

	void DustSpawn(char _Input);

	void DeadRender();

	void RenderCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map);
	bool RenderCheckHelper(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile, BabaState _State);
	std::string PrevAnimation = "";
private:
	std::stack<bool> Move_Stack = {};
	std::stack<int> Type_Stack = {};
	float4 Color;
	float2D Location2D{};
	float2D NextLocation2D{};
	TilePoint PrevTile = { 0,0 };
	bool IsChecked = false;
	bool CanMove = false;
	bool Dead = false;
	void PrevStaticState();
	int Move_Stack_Size = 0;
};

