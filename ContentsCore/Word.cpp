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

void AWord::IsCheck(std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');

	BabaState LeftWord = WorldCheck(_Map, ATile);

	if (BabaState::IsWord != LeftWord) {
		return;
	}
	TilePoint DTile = this->KeyTileReturn('D');


	BabaState RightWord = WorldCheck(_Map, DTile);

	if (BabaState::IsNone == RightWord) {
		return;
	}

	ActiveUpdate(LeftWord, RightWord);


}

BabaState AWord::WorldCheck(std::map<__int64, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile.Location];
	if (_List.empty() == true) {
		return BabaState::IsNone;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->BState == BabaState::IsWord) {
			return BabaState::IsWord;
		}
		else if (_Baba->BState == BabaState::IsActive) {
			return BabaState::IsActive;
		}
	}
	return BabaState::IsNone;

}

void AWord::ActiveUpdate(BabaState _Left, BabaState _Right)
{
	ActiveState* Who = nullptr;
	switch (_Left)
	{
	case BabaState::IsBaba:
		Who = &BabaUpdateHelper::ActiveBaba;
		break;
	case BabaState::IsRock:
		Who = &BabaUpdateHelper::ActiveRock;
		break;
	default:
		return;
		break;
	}
	if (BabaState::IsWord == _Right) {
		WordChange(Who, _Right);
	}
	else if (BabaState::IsActive == _Right) {
		ActiveChange(Who, _Right);
	}
}

void AWord::WordChange(ActiveState* _CurWord, BabaState _Which)
{

}

void AWord::ActiveChange(ActiveState* _CurWord, BabaState _Which)
{

}

// isbaba, ismove, ispush
