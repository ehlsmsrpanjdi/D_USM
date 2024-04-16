#include "PreCompile.h"
#include "ContentsHelper.h"

ActiveState BabaUpdateHelper::ActiveBaba = {false, false, true};
ActiveState BabaUpdateHelper::ActiveRock = { false, true, false};

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
