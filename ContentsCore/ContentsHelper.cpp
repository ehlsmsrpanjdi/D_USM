#include "PreCompile.h"
#include "ContentsHelper.h"

ActiveState BabaUpdateHelper::ActiveBaba = { false, false, true, false, false };
ActiveState BabaUpdateHelper::ActiveRock = { false, false, false, false, false };
ActiveState BabaUpdateHelper::ActiveWord = { false, true, false , false, false };

ActiveState BabaUpdateHelper::Push = { false, true, false  , false, false };
ActiveState BabaUpdateHelper::Move = { false, false, true  , false, false };
ActiveState BabaUpdateHelper::None = { false, false, false  , false, false };
ActiveState BabaUpdateHelper::Stop = { false, false, false  , true, false };
ActiveState BabaUpdateHelper::Pull = { false, false, false  , false, true };

BabaState BabaUpdateHelper::Baba = BabaState::IsBaba;
BabaState BabaUpdateHelper::Rock = BabaState::IsRock;

float ContentsHelper::Time = 2.f;

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
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
