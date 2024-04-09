#include "PreCompile.h"
#include "ContentsHelper.h"



float ContentsHelper::Time = 0.f;

ContentsHelper::ContentsHelper()
{
}

ContentsHelper::~ContentsHelper()
{
}

void ContentsHelper::CoolTimeCheck(float _DeltaTime)
{
	if (Time <= MoveTime) {
		Time += _DeltaTime * 10.f;
	}
	else {
		Time = MoveTime;
	}
}
