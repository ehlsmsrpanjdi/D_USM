#include "PreCompile.h"
#include "HasWord.h"
#include "NameWord.h"
#include "ActiveWord.h"
#include <EngineCore/Actor.h>
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>

HasWord::HasWord()
{

}

HasWord::~HasWord()
{
}

void HasWord::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");
	Renderer->CreateAnimation("HasOn", "Is.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{0,3,6});
	Renderer->CreateAnimation("Has", "Has.png", std::vector<float>{0.1f, 0.1f, 0.1f}, std::vector<int>{1, 4, 7});
	Renderer->ChangeAnimation("Has");
}

void HasWord::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	 
	ABabaBase::Tick(_DeltaTime);
	if (IsOn == true) {
		Renderer->ChangeAnimation("HasOn");
	}
	else {
		Renderer->ChangeAnimation("Has");
	}
}

void HasWord::UpCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('W');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

	if (nullptr == LeftWord) {
		return;
	}

	TilePoint DTile = this->KeyTileReturn('S');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (nullptr == RightWord) {
		return;
	}
	NameWord* RightName = dynamic_cast<NameWord*>(RightWord);

	LeftWord->HasState = RightName->GetNameSet();

}

void HasWord::AxisCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint ATile = this->KeyTileReturn('A');

	ABabaBase* LeftWord = WorldCheck(_Map, ATile);

	if (nullptr == LeftWord) {
		return;
	}

	TilePoint DTile = this->KeyTileReturn('D');


	ABabaBase* RightWord = WorldCheck(_Map, DTile);

	if (nullptr == RightWord) {
		return;
	}
	NameWord* RightName = dynamic_cast<NameWord*>(RightWord);

	LeftWord->HasState = RightName->GetNameSet();

}

ABabaBase* HasWord::WorldCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
	if (_List.empty() == true) {
		return nullptr;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->GetBstate() == BabaState::IsWord) {
			return _Baba;
		}
	}
	return nullptr;
}



