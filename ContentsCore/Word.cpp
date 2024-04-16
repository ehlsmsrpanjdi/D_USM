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

void AWord::IsCheck(std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');
	
	BabaState LeftWord = BabaState::IsNone;

	if (false == WorldCheck(_Map, ATile, LeftWord)) {
		return;
	}
	if (LeftWord == BabaState::IsActive) {
		return;
	}

	BabaState RightWord = BabaState::IsNone;

	if (false == WorldCheck(_Map, ATile, LeftWord)) {
		return;
	}





}

bool AWord::WorldCheck(std::map<__int64, std::list<ABabaBase*>>& _Map, TilePoint _Tile, BabaState _Baba)
{
	std::list<ABabaBase*>& _List = _Map[_Tile.Location];
	if (_List.empty() == true) {
		return false;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->BState == BabaState::IsWord) {
			return true;
		}
	}

}

void AWord::BabaUpdate()
{
}

// isbaba, ismove, ispush
