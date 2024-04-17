#include "PreCompile.h"
#include "ContentsHelper.h"

ActiveState BabaUpdateHelper::ActiveBaba = {false, false, true};
ActiveState BabaUpdateHelper::ActiveRock = { false, false, false};
ActiveState BabaUpdateHelper::ActiveWord = { false, true, false };

ActiveState BabaUpdateHelper::Push = { false, true, false };
ActiveState BabaUpdateHelper::Move = { false, false, true };
ActiveState BabaUpdateHelper::None = { false, false, false };

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
