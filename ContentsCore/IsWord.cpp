#include "PreCompile.h"
#include "IsWord.h"
#include "NameWord.h"
#include "ActiveWord.h"
#include <EngineCore/Actor.h>


IsWord::IsWord()
{
}

IsWord::~IsWord()
{
}

void IsWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer
}

void IsWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
}

void IsWord::UpCheck(std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

	if (BabaState::IsWord != LeftWord->GetBstate()) {
		return;
	}
	TilePoint DTile = this->KeyTileReturn('D');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (BabaState::IsNone == RightWord->GetBstate()) {
		return;
	}

	ActiveUpdate(LeftWord, RightWord);


}

void IsWord::AxisCheck(std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('W');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

	if (BabaState::IsWord != LeftWord->GetBstate()) {
		return;
	}
	TilePoint DTile = this->KeyTileReturn('S');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (BabaState::IsNone == RightWord->GetBstate()) {
		return;
	}

	ActiveUpdate(LeftWord, RightWord);

}

ABabaBase* IsWord::WorldCheck(std::map<__int64, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile.Location];
	if (_List.empty() == true) {
		return nullptr;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->GetBstate() == BabaState::IsWord) {
			return _Baba;
		}
		else if (_Baba->GetBstate() == BabaState::IsActive) {
			return _Baba;
		}
	}
	return nullptr;

	//std::list<ABabaBase*>& _List = _Map[_Tile.Location];
	//if (_List.empty() == true) {
	//	return BabaState::IsNone;
	//}
	//for (ABabaBase* _Baba : _List) {
	//	if (_Baba->BState == BabaState::IsWord) {
	//		return BabaState::IsWord;
	//	}
	//	else if (_Baba->BState == BabaState::IsActive) {
	//		return BabaState::IsActive;
	//	}
	//}
	//return BabaState::IsNone;

}

void IsWord::ActiveUpdate(ABabaBase* _Left, ABabaBase* _Right)
{
	ActiveState* Who = nullptr;
	NameWord* _LeftName = dynamic_cast<NameWord*>(_Left);
	switch (_LeftName->GetNameSet())
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

	if (BabaState::IsWord == _Right->GetBstate()) {
		WordChange(Who, _Right);
	}
	else if (BabaState::IsActive == _Right->GetBstate()) {
		ActiveChange(Who, _Right);
	}
}

void IsWord::WordChange(ActiveState* _CurWord, ABabaBase* _Name)
{
	NameWord* Name = dynamic_cast<NameWord*>(_Name);
	Name->GetNameSet();
}

void IsWord::ActiveChange(ActiveState* _CurWord, ABabaBase* _Active)
{
	ActiveWord* Active = dynamic_cast<ActiveWord*>(_Active);
	ActiveInfo Info = Active->GetActive();
	_CurWord->IsFloat = _CurWord->IsFloat || Info.IsFloat;
	_CurWord->IsPush = _CurWord->IsPush || Info.IsPush;
	_CurWord->IsMove = _CurWord->IsMove || Info.IsMove;
}

// isbaba, ismove, ispush
