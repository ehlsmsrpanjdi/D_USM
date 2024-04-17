#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"

class ABabaBase;
class IsWord;
class NameWord;
class ActiveWord;
// ���� :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

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
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	char Key = '0';
	std::map <__int64, std::list<ABabaBase*>> Baba_Actors;
	std::vector<ABabaBase*> Change_Baba;
	std::vector<IsWord*> Is_Vec;
	std::stack<char> Stack_Input;
	bool IsInput = false;
	int Count = 0;

	void Baba_Input();

	void Stack_Push(char _Key);
	void Stack_Pop();
	void Change_BabaPos();
	void BabaInputCheck();
	void DebugMessageFunction();
	
	void WordUpdate();
	void IsUpdate();

	std::shared_ptr<IsWord> SpawnIs(TilePoint _Tile);
	std::shared_ptr<NameWord> SpawnName(TilePoint _Tile, BabaState _Info);
	std::shared_ptr<ActiveWord> SpawnActive(TilePoint _Tile, ActiveState _Info);

	std::shared_ptr<IsWord> SpawnIs(int _X, int _Y) {
		return SpawnIs(TilePoint(_X, _Y));
	}
	std::shared_ptr<NameWord> SpawnName(int _X, int _Y, BabaState _Info) {
		return SpawnName(TilePoint(_X, _Y),_Info);
	}
	std::shared_ptr<ActiveWord> SpawnActive(int _X, int _Y, ActiveState _Info) {
		return SpawnActive(TilePoint(_X, _Y), _Info);
	}
private:

	bool CanInput = false;
};

