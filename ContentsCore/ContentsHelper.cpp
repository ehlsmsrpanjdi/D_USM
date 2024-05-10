#include "PreCompile.h"
#include "ContentsHelper.h"
#include "BabaBase.h"
#include "PlayGameMode.h"
#include "IsWord.h"
#include "ActiveWord.h"
#include "AndWord.h"
#include "FadeINEffect.h"
#include "FadeOUTEffect.h"
#include "BackGround.h"


ActiveState BabaUpdateHelper::ActiveBaba;
ActiveState BabaUpdateHelper::ActiveRock;
ActiveState BabaUpdateHelper::ActiveWord;
ActiveState BabaUpdateHelper::ActiveWall;
ActiveState BabaUpdateHelper::ActiveSkull;
ActiveState BabaUpdateHelper::ActiveFlag;
ActiveState BabaUpdateHelper::ActiveWater;
ActiveState BabaUpdateHelper::ActiveLava;
ActiveState BabaUpdateHelper::ActiveGrass;
ActiveState BabaUpdateHelper::ActiveIce;
ActiveState BabaUpdateHelper::ActiveAlgae;
ActiveState BabaUpdateHelper::ActiveBox;
ActiveState BabaUpdateHelper::ActiveDoor;
ActiveState BabaUpdateHelper::ActiveCrab;
ActiveState BabaUpdateHelper::ActiveJelly;
ActiveState BabaUpdateHelper::ActivePillar;
ActiveState BabaUpdateHelper::ActiveKey;
ActiveState BabaUpdateHelper::ActiveStar;

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
ActiveState BabaUpdateHelper::Melt;
ActiveState BabaUpdateHelper::Open;
ActiveState BabaUpdateHelper::Shut;

BabaState BabaUpdateHelper::Baba = BabaState::IsBaba;
BabaState BabaUpdateHelper::Rock = BabaState::IsRock;
BabaState BabaUpdateHelper::Wall = BabaState::IsWall;
BabaState BabaUpdateHelper::Flag = BabaState::IsFlag;
BabaState BabaUpdateHelper::Skull = BabaState::IsSkull;
BabaState BabaUpdateHelper::Water = BabaState::IsWater;
BabaState BabaUpdateHelper::Lava = BabaState::IsLava;
BabaState BabaUpdateHelper::Grass = BabaState::IsGrass;
BabaState BabaUpdateHelper::Ice = BabaState::IsIce;
BabaState BabaUpdateHelper::Algae = BabaState::IsAlgae;
BabaState BabaUpdateHelper::Box = BabaState::IsBox;
BabaState BabaUpdateHelper::Door = BabaState::IsDoor;
BabaState BabaUpdateHelper::Crab = BabaState::IsCrab;
BabaState BabaUpdateHelper::Jelly = BabaState::IsJelly;
BabaState BabaUpdateHelper::Pillar = BabaState::IsPillar;
BabaState BabaUpdateHelper::Key = BabaState::IsKey;
BabaState BabaUpdateHelper::Star = BabaState::IsStar;

float ContentsHelper::Time = 1.f;

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
	BabaUpdateHelper::Melt.IsMelt = true;
	BabaUpdateHelper::Open.IsOpen= true;
	BabaUpdateHelper::Shut.IsShut = true;

}

enum class Fade {
	FadeNone,
	FadeIn,
	FadeOut,
};


float ContentsHelper::EffectTime = 0.0f;
std::shared_ptr<FadeINEffect> ContentsHelper::FadeIn = nullptr;
std::shared_ptr<FadeOUTEffect> ContentsHelper::FadeOut = nullptr;
Fade ContentsHelper::FadeNum = Fade::FadeNone;


void ContentsHelper::FadeEffectIn(ULevel* _Level)
{
	ContentsHelper::FadeNum = Fade::FadeIn;
	EffectTime = 2.0f;
	FadeIn->ResetTime();
	if (nullptr == ContentsHelper::FadeIn) {
		ContentsHelper::FadeIn = _Level->GetLastTarget()->AddEffect<FadeINEffect>();
	}
	else {
		FadeIn->EffectON();
	}
}

void ContentsHelper::FadeEffectOut(ULevel* _Level)
{
	ContentsHelper::FadeNum = Fade::FadeOut;
	EffectTime = 2.0f;
	if (nullptr == ContentsHelper::FadeOut) {
	ContentsHelper::FadeOut = _Level->GetLastTarget()->AddEffect<FadeOUTEffect>();
	}
	else {
	FadeOut->EffectON();
	}
}

void ContentsHelper::FadeOutHelper(ULevel* _Level) {

}
void ContentsHelper::FadeInHelper(ULevel* _Level) {

}

void ContentsHelper::CoolTimeCheck(float _DeltaTime)
{
	if (Time < MoveTime) {
		Time += _DeltaTime * 10.f;
	}
	else {
		Time = MoveTime;
	}

	if (EffectTime > 0) {
		EffectTime -= _DeltaTime;
	}
	else if(FadeNum != Fade::FadeNone) {
		if (FadeNum == Fade::FadeIn) {
			FadeIn->ResetTime();
			FadeIn->EffectOff();
			GEngine->ChangeLevel("SelectGameLevel");
			float4 BackSize = BackGroundImage::Back->Size;
			BackGroundImage::Back->AddRenderSize(-BackSize);
		}
		if (FadeNum == Fade::FadeOut) {
			FadeOut->ResetTime();
			FadeOut->EffectOff();
			GEngine->ChangeLevel("SelectGameLevel");
		}
		FadeNum = Fade::FadeNone;
	}
}


