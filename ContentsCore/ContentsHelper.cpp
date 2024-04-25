#include "PreCompile.h"
#include "ContentsHelper.h"

ActiveState BabaUpdateHelper::ActiveBaba;
ActiveState BabaUpdateHelper::ActiveRock;
ActiveState BabaUpdateHelper::ActiveWord;
ActiveState BabaUpdateHelper::ActiveWall;
ActiveState BabaUpdateHelper::ActiveSkull;
ActiveState BabaUpdateHelper::ActiveFlag;
ActiveState BabaUpdateHelper::ActiveWater;
ActiveState BabaUpdateHelper::ActiveLava;
ActiveState BabaUpdateHelper::ActiveGrass;

ActiveState BabaUpdateHelper::None;
ActiveState BabaUpdateHelper::Float;
ActiveState BabaUpdateHelper::Push;
ActiveState BabaUpdateHelper::Move;
ActiveState BabaUpdateHelper::Stop;
ActiveState BabaUpdateHelper::Pull;
ActiveState BabaUpdateHelper::Win;
ActiveState BabaUpdateHelper::Defeat;
ActiveState BabaUpdateHelper::Hot;
ActiveState BabaUpdateHelper::Sink;
ActiveState BabaUpdateHelper::You;

BabaState BabaUpdateHelper::Baba = BabaState::IsBaba;
BabaState BabaUpdateHelper::Rock = BabaState::IsRock;
BabaState BabaUpdateHelper::Wall = BabaState::IsWall;
BabaState BabaUpdateHelper::Flag = BabaState::IsFlag;
BabaState BabaUpdateHelper::Skull = BabaState::IsSkull;
BabaState BabaUpdateHelper::Water = BabaState::IsWater;
BabaState BabaUpdateHelper::Lava = BabaState::IsLava;

float ContentsHelper::Time = 2.f;

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

void ContentsHelper::WordInit()
{
	//bool IsFloat = true;
	//bool IsPush = true;
	//bool IsMove = true;
	//bool IsStop = true;
	//bool IsPull = true;
	//bool IsWin = true;
	//bool IsDefeat = true;
	//bool IsHot = true;
	//bool IsSink = true;

	BabaUpdateHelper::None;
	BabaUpdateHelper::Float.IsFloat = true;
	BabaUpdateHelper::Push.IsPush = true;
	BabaUpdateHelper::Move.IsMove = true;
	BabaUpdateHelper::Stop.IsStop = true;
	BabaUpdateHelper::Pull.IsPull = true;
	BabaUpdateHelper::Win.IsWin = true;
	BabaUpdateHelper::Defeat.IsDefeat = true;
	BabaUpdateHelper::Hot.IsHot = true;
	BabaUpdateHelper::Sink.IsSink = true;
	BabaUpdateHelper::You.IsYou = true;
	BabaUpdateHelper::You.IsMove = true;
}

void ContentsHelper::CoolTimeCheck(float _DeltaTime)
{
	if (Time < MoveTime) {
		Time += _DeltaTime * 10.f;
	}
	else {
		Time = MoveTime;
	}
}