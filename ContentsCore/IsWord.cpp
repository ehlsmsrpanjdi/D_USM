#include "PreCompile.h"
#include "IsWord.h"
#include "NameWord.h"
#include "ActiveWord.h"
#include <EngineCore/Actor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

IsWord::IsWord()
{

}

IsWord::~IsWord()
{
}

void IsWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");
	Renderer->CreateAnimation("Is", "Is.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0, 2, 4});
	Renderer->ChangeAnimation("is");
}

void IsWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ABabaBase::Tick(_DeltaTime);
}

void IsWord::UpCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('W');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

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

void IsWord::AxisCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

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

ABabaBase* IsWord::WorldCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
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

void IsWord::ActiveUpdate(ABabaBase* _Left, ABabaBase* _Right)
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
		default:
			return;
			break;
		}
		ActiveChange(Who, _Right);
	}
}

void IsWord::WordChange(ABabaBase* _CurWord, ABabaBase* _Name)
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
	default:
		break;
	}

	*State = BackWord->GetNameSet();
}

void IsWord::ActiveChange(ActiveState* _CurWord, ABabaBase* _Active)
{
	ActiveWord* Active = dynamic_cast<ActiveWord*>(_Active);
	ActiveState Info = Active->GetActive();
	_CurWord->IsFloat = _CurWord->IsFloat || Info.IsFloat;
	_CurWord->IsPush = _CurWord->IsPush || Info.IsPush;
	_CurWord->IsMove = _CurWord->IsMove || Info.IsMove;
}

// isbaba, ismove, ispush