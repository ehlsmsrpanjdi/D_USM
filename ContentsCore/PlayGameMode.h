#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"

class ABabaBase;
class IsWord;
class NameWord;
class ActiveWord;
class AndWord;
class HasWord;
class BottomTile;

// Ό³Έν :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
	friend class ContentsHelper;
	friend class BabaEditor;

public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _NextLevel) override;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	char Key = '0';
	std::map <TilePoint, std::list<ABabaBase*>> Baba_Actors;
	std::vector<ABabaBase*> Change_Baba;
	std::vector<IsWord*> Is_Vec;
	std::vector<AndWord*> And_Vec;
	std::vector<HasWord*> Has_Vec;
	std::stack<char> Stack_Input;
	bool IsInput = false;
	int Count = 0;

	float NotMoveTime = 0.f;

	bool RestartCheck();
	void Baba_Input();

	void Stack_Push(char _Key);
	void Stack_Pop();
	void Change_BabaPos();
	void BabaInputCheck();
	void DebugMessageFunction();

	void IsReset();
	void DeadReset();
	void IsUpdate();
	void AndUpdate();
	void HasUpdate();

	void HotCheck();
	void DefeatCheck();
	void WinCheck();
	void SinkCheck();
	std::list<ABabaBase*> SinkBaba = { nullptr, };
	void DoorOpenCheck();
	std::list<ABabaBase*> OpenBaba = { nullptr, };

	ActiveState GetActive(const BabaState& State);


	std::shared_ptr<IsWord> SpawnIs(TilePoint _Tile);
	std::shared_ptr<AndWord> SpawnAnd(TilePoint _Tile);
	std::shared_ptr<HasWord> SpawnHas(TilePoint _Tile);
	std::shared_ptr<NameWord> SpawnName(TilePoint _Tile, BabaState _Info);
	std::shared_ptr<ActiveWord> SpawnActive(TilePoint _Tile, std::string_view _Str);
	std::shared_ptr<ABabaBase> SpawnBaba(TilePoint _Tile, std::string_view _Str);

	std::shared_ptr<IsWord> SpawnIs(int _X, int _Y) {
		return SpawnIs(TilePoint(_X, _Y));
	}
	std::shared_ptr<NameWord> SpawnName(int _X, int _Y, BabaState _Info) {
		return SpawnName(TilePoint(_X, _Y), _Info);
	}
	std::shared_ptr<ActiveWord> SpawnActive(int _X, int _Y, std::string_view _Str) {
		return SpawnActive(TilePoint(_X, _Y), _Str);
	}

	std::shared_ptr<ABabaBase> SpawnBaba(int _X, int _Y, std::string_view _Str) {
		return SpawnBaba(TilePoint(_X, _Y), _Str);
	}

	std::shared_ptr<AndWord> SpawnAnd(int _X, int _Y) {
		return SpawnAnd(TilePoint(_X, _Y));
	}

	std::shared_ptr<HasWord> SpawnHas(int _X, int _Y) {
		return SpawnHas(TilePoint(_X, _Y));
	}

	std::shared_ptr<BottomTile> SpawnTile(int _X, int _Y) {
		return SpawnTile(TilePoint(_X, _Y));
	}

	std::shared_ptr<BottomTile> SpawnTile(TilePoint _Tile);



private:
	void ContainerReset();
	bool CanInput = false;
};

