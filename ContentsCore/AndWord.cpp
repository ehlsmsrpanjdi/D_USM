#include "PreCompile.h"
#include "AndWord.h"
#include "NameWord.h"
#include "ActiveWord.h"
#include <EngineCore/Actor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

AndWord::AndWord()
{

}

AndWord::~AndWord()
{
}

void AndWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");
	Renderer->CreateAnimation("And", "And.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 3, 6});
	Renderer->ChangeAnimation("And");
}

void AndWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}

void AndWord::UpCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('W');

	bool Check = WordOnCheck(_Map, ATile);

	if (false == Check) {
		return;
	}

	TilePoint UpTile = GetTile() + TilePoint{ 0,3 };

	ABabaBase* LeftWord = WorldCheck(_Map, UpTile);

	if (nullptr == LeftWord) {
		return;
	}
	if (BabaState::IsWord != LeftWord->GetBstate()) {
		return;
	}

	TilePoint DTile = this->KeyTileReturn('S');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (nullptr == RightWord) {
		return;
	}

	if (BabaState::IsNone == RightWord->GetBstate()) {
		return;
	}

	ActiveUpdate(LeftWord, RightWord);


}

void AndWord::AxisCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');

	bool Check = WordOnCheck(_Map, ATile);

	if (false == Check) {
		return;
	}

	TilePoint LeftTile = GetTile() + TilePoint{ -3,0 };

	ABabaBase* LeftWord = WorldCheck(_Map, LeftTile);

	if (nullptr == LeftWord) {
		return;
	}
	if (BabaState::IsWord != LeftWord->GetBstate()) {
		return;
	}

	TilePoint DTile = this->KeyTileReturn('D');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (nullptr == RightWord) {
		return;
	}

	if (BabaState::IsNone == RightWord->GetBstate()) {
		return;
	}

	ActiveUpdate(LeftWord, RightWord);



}

ABabaBase* AndWord::WorldCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
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
}

bool AndWord::WordOnCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
	if (_List.empty() == true) {
		return false;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->GetBstate() == BabaState::IsWord) {
			if (_Baba->IsOn = true) {
				return true;
			}
			else {
				return false;
			}
		}
		else if (_Baba->GetBstate() == BabaState::IsActive) {
			if (_Baba->IsOn = true) {
				return true;
			}
			else {
				return false;
			}
		}
	}
	return false;
}

void AndWord::ActiveUpdate(ABabaBase* _Left, ABabaBase* _Right)
{
	ActiveState* Who = nullptr;


	if (BabaState::IsWord == _Right->GetBstate()) {

		WordChange(_Left, _Right);
	}

	else if (BabaState::IsActive == _Right->GetBstate()) {
		NameWord* _LeftName = dynamic_cast<NameWord*>(_Left);
		switch (_LeftName->GetNameSet())
		{
		case BabaState::IsBaba:
			Who = &BabaUpdateHelper::ActiveBaba;
			break;
		case BabaState::IsRock:
			Who = &BabaUpdateHelper::ActiveRock;
			break;
		case BabaState::IsWall:
			Who = &BabaUpdateHelper::ActiveWall;
			break;
		case BabaState::IsFlag:
			Who = &BabaUpdateHelper::ActiveFlag;
			break;
		case BabaState::IsSkull:
			Who = &BabaUpdateHelper::ActiveSkull;
			break;
		case BabaState::IsWater:
			Who = &BabaUpdateHelper::ActiveWater;
			break;
		case BabaState::IsLava:
			Who = &BabaUpdateHelper::ActiveLava;
			break;
		}
		ActiveChange(Who, _Right);
	}
}

void AndWord::WordChange(ABabaBase* _CurWord, ABabaBase* _Name)
{
	NameWord* FrontWord = dynamic_cast<NameWord*>(_CurWord);
	NameWord* BackWord = dynamic_cast<NameWord*>(_Name);
	BabaState FrontName = FrontWord->GetNameSet();
	BabaState* State = nullptr;
	switch (FrontName)
	{
	case BabaState::IsBaba:
		State = &BabaUpdateHelper::Baba;
		break;
	case BabaState::IsRock:
		State = &BabaUpdateHelper::Rock;
		break;
	case BabaState::IsWall:
		State = &BabaUpdateHelper::Wall;
		break;
	case BabaState::IsFlag:
		State = &BabaUpdateHelper::Flag;
		break;
	case BabaState::IsSkull:
		State = &BabaUpdateHelper::Skull;
		break;
	case BabaState::IsWater:
		State = &BabaUpdateHelper::Water;
		break;
	case BabaState::IsLava:
		State = &BabaUpdateHelper::Lava;
		break;
	}

	*State = BackWord->GetNameSet();
}

void AndWord::ActiveChange(ActiveState* _CurWord, ABabaBase* _Active)
{
	//bool IsFloat = false;
	//bool IsPush = false;
	//bool IsMove = false;
	//bool IsStop = false;
	//bool IsPull = false;
	//bool IsWin = false;
	//bool IsDefeat = false;
	//bool IsHot = false;
	//bool IsSink = false;


	ActiveWord* Active = dynamic_cast<ActiveWord*>(_Active);
	ActiveState Info = Active->GetActive();
	_CurWord->IsFloat = _CurWord->IsFloat || Info.IsFloat;
	_CurWord->IsPush = _CurWord->IsPush || Info.IsPush;
	_CurWord->IsMove = _CurWord->IsMove || Info.IsMove;
	_CurWord->IsStop = _CurWord->IsStop || Info.IsStop;
	_CurWord->IsPull = _CurWord->IsPull || Info.IsPull;
	_CurWord->IsWin = _CurWord->IsWin || Info.IsWin;
	_CurWord->IsDefeat = _CurWord->IsDefeat || Info.IsDefeat;
	_CurWord->IsHot = _CurWord->IsHot || Info.IsHot;
	_CurWord->IsSink = _CurWord->IsSink || Info.IsSink;
}

// isbaba, ismove, ispush