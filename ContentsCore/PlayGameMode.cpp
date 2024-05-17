#include "PreCompile.h"
#include "PlayGameMode.h"
#include "BabaBase.h"
#include "PlayBack.h"
#include <EngineCore/Camera.h>
#include "ContentsHelper.h"
#include "TileMap.h"
#include <iterator>
#include <EngineCore/EngineDebugMsgWindow.h>
#include <EngineCore/EngineCore.h>
#include "IsWord.h"
#include "NameWord.h"
#include "ActiveWord.h"
#include "BabaEditor.h"
#include "FadeINEffect.h"
#include "FadeOUTEffect.h"
#include "ContentsHelper.h"
#include "AndWord.h"
#include "HasWord.h"
#include "BackGround.h"
#include "BottomTile.h"
#include "ContentsCore.h"
#include "BackBackGround.h"


APlayGameMode::APlayGameMode()
{

}

APlayGameMode::~APlayGameMode()
{}

void APlayGameMode::LevelEnd(ULevel* _NextLevel)
{
	float4 BackSize = BackGroundImage::Back->Size;
	BackGroundImage::Back->AddRenderSize(-BackSize);
}

void APlayGameMode::LevelStart(ULevel* _NextLevel)
{
	ContentsCore::Editor->GameMode = this;
	TileMap::TileSet(30, 30);

	InputOn();
}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	BackGroundImage::Back = GetWorld()->SpawnActor<BackGround>("a").get();
	//Camera->AddActorLocation(FVector(450.f, 300.0f, -100.0f));
	BackGroundImage::Back->SetActorLocation(FVector(0,0,300));
	ContentsCore::GameMode = this;

	GetWorld()->SpawnActor<BackBackGround>("A");

	ContentsHelper::WordInit();
	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	//BackGroundImage::Back->AddActorLocation(FVector{ 10.f,10.f } *_DeltaTime);
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	if (false == RestartCheck()) {
		NotMoveTime += _DeltaTime;
	}
	else {
		NotMoveTime = 0.f;
	}
	if (ContentsHelper::Time >= 1) {
		CanInput = true;
	}
	else {
		CanInput = false;
	}
	if (CanInput == true) {
		IsReset();
		IsUpdate();
		AndUpdate();
		HasUpdate();
		BabaInputCheck();
	}
	DebugMessageFunction();

	if (NotMoveTime >= 3.0f) {
		int a = 0;
	}

	if (IsDown(VK_ESCAPE)) {
		GEngine->ChangeLevel("SelectGameLevel");
	}

}

bool APlayGameMode::RestartCheck()
{
	bool CanActive = false;
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			if (_BabaBase->IsChecked == true) {
				continue;
			}
			if (_BabaBase->MoveCheck() == false) {
				continue;
			}
			bool Temp = false;;
			Temp |= _BabaBase->BabaMoveResetCheck('A', Baba_Actors);
			Temp |= _BabaBase->BabaMoveResetCheck('S', Baba_Actors);
			Temp |= _BabaBase->BabaMoveResetCheck('D', Baba_Actors);
			Temp |= _BabaBase->BabaMoveResetCheck('W', Baba_Actors);
			CanActive = (CanActive || Temp);
		}
	}
	return CanActive;
}

void APlayGameMode::Baba_Input()
{
	switch (Key)
	{
	case 'W':
	case 'A':
	case 'S':
	case 'D':
		Stack_Push(Key);
		break;
	case 'Z':
		Stack_Pop();
		break;
	default:
		break;
	}
}

void APlayGameMode::Stack_Push(char _Key)
{
	Stack_Input.push(_Key);
	ContentsHelper::Time = 0.f;

	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			_BabaBase->SetKey(_Key);
			_BabaBase->LerpMove();
		}
	}

}
void APlayGameMode::Stack_Pop()
{
	char Temp_Key;
	if (Stack_Input.empty() != true) {
		Temp_Key = Stack_Input.top();
		Stack_Input.pop();
		ContentsHelper::Time = 0.f;
		for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			if (BabaBase.empty() == true) {
				continue;
			}
			for (ABabaBase*& _BabaBase : BabaBase) {
				_BabaBase->SetKey(Temp_Key);
				_BabaBase->PopLerpMove();
				Change_Baba.push_back(_BabaBase);
			}
		}
	}
}

void APlayGameMode::Change_BabaPos()
{
	for (ABabaBase*& ChangeBabas : Change_Baba) {
		ChangeBabas->ChangeTile(Baba_Actors);
	}
	Change_Baba.clear();
}

void APlayGameMode::BabaInputCheck()
{
	if (ContentsHelper::Time >= 1) {
		for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			for (ABabaBase*& _BabaBase : BabaBase) {
				_BabaBase->IsChecked = false;
			}
		}
		if (true == IsDown('A'))
		{
			Key = 'A';
			CanInput = false;
		}

		else if (true == IsDown('D'))
		{
			Key = 'D';
			CanInput = false;
		}

		else if (true == IsDown('W'))
		{
			Key = 'W';
			CanInput = false;
		}

		else if (true == IsDown('S'))
		{
			Key = 'S';
			CanInput = false;
		}
		else if (true == IsDown('Z'))
		{
			Stack_Pop();
			Change_BabaPos();
			DeadReset();
			HotCheck();
			SinkCheck();
			DoorOpenCheck();
			WinCheck();
			DefeatCheck();
			CanInput = false;
			return;
		}
		else {
			Key = '0';
			return;
		}
		bool CanActive = false;
		for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
		{
			std::list<ABabaBase*>& BabaBase = Iter.second;
			for (ABabaBase*& _BabaBase : BabaBase) {
				if (_BabaBase->IsChecked == true) {
					continue;
				}
				if (_BabaBase->MoveCheck() == false) {
					continue;
				}
				bool Temp = _BabaBase->BabaMoveCheck(Key, Change_Baba, Baba_Actors);
				CanActive = (CanActive || Temp);
			}
		}
		if (true == CanActive) {
			Baba_Input();
			Change_BabaPos();
			DeadReset();
			HotCheck();
			SinkCheck();
			DoorOpenCheck();
			WinCheck();

			DefeatCheck();
		}
		else {
		}
	}
}

void APlayGameMode::DebugMessageFunction()
{
	//{
	//	std::string Msg = std::format("Change BABA : {}\n", std::to_string(Change_Baba.size()));
	//	BabaEditor::PushMsg(Msg);
	//}

}

void APlayGameMode::IsReset()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase)
		{
			if (_BabaBase->IsDestroy() == true) {
				continue;
			}

			if (_BabaBase == nullptr) {
				continue;
			}
			_BabaBase->IsChecked = false;
			_BabaBase->CanMove = false;
			_BabaBase->IsOn = false;
			_BabaBase->RenderCheck(Baba_Actors);
		}
	}
	BabaUpdateHelper::ActiveBaba = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveRock = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveWord = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveWall = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveSkull = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveFlag = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveWater = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveLava = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveGrass = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveIce = BabaUpdateHelper::None;
}

void APlayGameMode::DeadReset()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			_BabaBase->SetDead(false);
		}
	}
	for (ABabaBase* FirstSink : SinkBaba) {
		if (FirstSink == nullptr) continue;
		for (ABabaBase* SecondSink : SinkBaba) {
			if (SecondSink == nullptr) continue;
			if (FirstSink == SecondSink) continue;
			if (FirstSink->GetTile() == SecondSink->GetTile()) {
				FirstSink->SetDead(true);
				SecondSink->SetDead(true);
			}
		}
	}
	for (ABabaBase* FirstSink : OpenBaba) {
		if (FirstSink == nullptr) continue;
		for (ABabaBase* SecondSink : OpenBaba) {
			if (SecondSink == nullptr) continue;
			if (FirstSink == SecondSink) continue;
			if (FirstSink->GetTile() == SecondSink->GetTile()) {
				FirstSink->SetDead(true);
				SecondSink->SetDead(true);
			}
		}
	}
}

void APlayGameMode::IsUpdate()
{
	BabaUpdateHelper::ActiveBaba = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveRock = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveWall = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveFlag = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveSkull = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveGrass = BabaUpdateHelper::None;
	BabaUpdateHelper::ActiveLava = BabaUpdateHelper::None;

	for (IsWord* _Is : Is_Vec) {
		_Is->UpCheck(Baba_Actors);
		_Is->AxisCheck(Baba_Actors);
	}
}

void APlayGameMode::AndUpdate()
{
	for (AndWord* _And : And_Vec) {
		_And->UpCheck(Baba_Actors);
		_And->AxisCheck(Baba_Actors);
		_And->DownCheck(Baba_Actors);
		_And->AxisRightCheck(Baba_Actors);
	}
}

void APlayGameMode::HasUpdate()
{
	for (HasWord* _Has : Has_Vec) {
		_Has->UpCheck(Baba_Actors);
		_Has->AxisCheck(Baba_Actors);
	}
}

void APlayGameMode::HotCheck()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			if (GetActive(_BabaBase->GetBstate()).IsHot == true) {
				TilePoint Tile = _BabaBase->GetTile();
				for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
					if (true == BabaUpdateHelper::StateToActive(_Baba->GetBstate()).IsMelt) {
						_Baba->SetDead(true);
					}
				}
			}
		}
	}
}

void APlayGameMode::SinkCheck()
{
	std::vector<ABabaBase*> temp;
	for (ABabaBase* Dead : SinkBaba) {
		if (Dead == nullptr) continue;
		if (Dead->GetDead() == false) {
			temp.push_back(Dead);
		}
	}
	for (ABabaBase* Dead : temp) {
		SinkBaba.remove(Dead);
	}
	temp.clear();
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			int SinkCount = 0;
			if (GetActive(_BabaBase->GetBstate()).IsSink == true) {
				if (true == _BabaBase->GetDead()) {
					continue;
				}
				TilePoint Tile = _BabaBase->GetTile();
				if (2 <= Baba_Actors[Tile].size()) {
					int i = 0;
					ABabaBase* TempBaba[2] = { nullptr, };
					for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
						TempBaba[i] = _Baba;
						SinkCount++;
						i++;
						if (SinkCount >= 2) {
							TempBaba[0]->SetDead(true);
							TempBaba[1]->SetDead(true);
							SinkBaba.push_back(TempBaba[0]);
							SinkBaba.push_back(TempBaba[1]);
							break;
						}
					}
				}
			}
		}
	}
	SinkBaba.unique();
}

void APlayGameMode::DoorOpenCheck()
{
	std::vector<ABabaBase*> temp;
	for (ABabaBase* Dead : OpenBaba) {
		if (Dead == nullptr) continue;
		if (Dead->GetDead() == false) {
			temp.push_back(Dead);
		}
	}
	for (ABabaBase* Dead : temp) {
		OpenBaba.remove(Dead);
	}
	temp.clear();
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			int OpenCount = 0;
			if (GetActive(_BabaBase->GetBstate()).IsShut == true) {
				if (true == _BabaBase->GetDead()) {
					continue;
				}
				TilePoint Tile = _BabaBase->GetTile();
				if (2 <= Baba_Actors[Tile].size()) {
					int i = 0;
					ABabaBase* TempBaba[2] = { nullptr, };
					bool OpenBool = false;
					bool ShutBool = false;
					for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
						if (_Baba->OpenCheck() == true && !OpenBool) {
							TempBaba[i] = _Baba;
							OpenBool = true;
							OpenCount++;
							i++;
						}
						if (_Baba->ShutCheck() == true && !ShutBool) {
							TempBaba[i] = _Baba;
							ShutBool = true;
							OpenCount++;
							i++;
						}
						if (OpenCount >= 2) {
							TempBaba[0]->SetDead(true);
							TempBaba[1]->SetDead(true);
							OpenBaba.push_back(TempBaba[0]);
							OpenBaba.push_back(TempBaba[1]);
							break;
						}
					}
				}
			}
		}
	}
	OpenBaba.unique();
}

void APlayGameMode::WinCheck()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			if (_BabaBase->GetDead() == true) {
				continue;
			}
			if (GetActive(_BabaBase->GetBstate()).IsWin == true) {
				TilePoint Tile = _BabaBase->GetTile();
				for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
					if (_Baba->GetDead() == true) {
						continue;
					}
					if (true == BabaUpdateHelper::StateToActive(_Baba->GetBstate()).IsYou) {
						InputOff();
						ContentsHelper::FadeEffectOut(GetWorld());
					}
				}
			}
		}
	}
}
void APlayGameMode::DefeatCheck()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			if (GetActive(_BabaBase->GetBstate()).IsDefeat == true) {
				if (_BabaBase->GetDead() == true) {
					continue;
				}
				TilePoint Tile = _BabaBase->GetTile();
				for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
					if (true == BabaUpdateHelper::StateToActive(_Baba->GetBstate()).IsYou) {
						_Baba->SetDead(true);
					}
				}
			}
		}
	}
}

ActiveState APlayGameMode::GetActive(const BabaState& State)
{
	switch (State)
	{
	case BabaState::IsBaba:
	{
		return BabaUpdateHelper::ActiveBaba;
	}
	break;
	case BabaState::IsRock:
	{
		return BabaUpdateHelper::ActiveRock;
	}
	break;
	case BabaState::IsWall:
	{
		return BabaUpdateHelper::ActiveWall;
	}
	break;
	case BabaState::IsFlag:
	{
		return BabaUpdateHelper::ActiveFlag;
	}
	break;
	case BabaState::IsSkull:
	{
		return BabaUpdateHelper::ActiveSkull;
	}
	break;
	case BabaState::IsLava:
	{
		return BabaUpdateHelper::ActiveLava;
	}
	break;
	case BabaState::IsWater:
	{
		return BabaUpdateHelper::ActiveWater;
	}
	break;
	case BabaState::IsStar:
	{
		return BabaUpdateHelper::ActiveStar;
	}
	break;
	case BabaState::IsCrab:
	{
		return BabaUpdateHelper::ActiveCrab;
	}
	break;
	case BabaState::IsBox:
	{
		return BabaUpdateHelper::ActiveBox;
	}
	break;
	case BabaState::IsDoor:
	{
		return BabaUpdateHelper::ActiveDoor;
	}
	break;
	case BabaState::IsJelly:
	{
		return BabaUpdateHelper::ActiveJelly;
	}
	break;
	case BabaState::IsPillar:
	{
		return BabaUpdateHelper::ActivePillar;
	}
	break;
	case BabaState::IsKey:
	{
		return BabaUpdateHelper::ActiveKey;
	}
	break;
	}
	return BabaUpdateHelper::None;
}

std::shared_ptr<IsWord> APlayGameMode::SpawnIs(TilePoint _Tile)
{
	std::shared_ptr<IsWord> Is = GetWorld()->SpawnActor<IsWord>("Word");
	Is->SetOrder(1);
	Is->StateInit(BabaState::IsWord);
	Is->SetBabaLocation(_Tile);
	Baba_Actors[Is->GetTile()].push_back(Is.get());
	Is_Vec.push_back(Is.get());
	return Is;
}

std::shared_ptr<AndWord> APlayGameMode::SpawnAnd(TilePoint _Tile)
{
	std::shared_ptr<AndWord> And = GetWorld()->SpawnActor<AndWord>("Word");
	And->SetOrder(1);
	And->StateInit(BabaState::IsIs);
	And->SetBabaLocation(_Tile);
	Baba_Actors[And->GetTile()].push_back(And.get());
	And_Vec.push_back(And.get());
	return And;
}

std::shared_ptr<HasWord> APlayGameMode::SpawnHas(TilePoint _Tile)
{
	std::shared_ptr<HasWord> Has = GetWorld()->SpawnActor<HasWord>("Word");
	Has->SetOrder(1);
	Has->StateInit(BabaState::IsHas);
	Has->SetBabaLocation(_Tile);
	Baba_Actors[Has->GetTile()].push_back(Has.get());
	Has_Vec.push_back(Has.get());
	return Has;
}

std::shared_ptr<NameWord> APlayGameMode::SpawnName(TilePoint _Tile, BabaState _Info)
{
	std::shared_ptr<NameWord> Name = GetWorld()->SpawnActor<NameWord>("Name");
	Name->SetOrder(1);
	Name->StateInit(BabaState::IsWord);
	Name->SetBabaLocation(_Tile);
	Name->SetNameSet(_Info);
	Name->NameWordChangeAnimation();
	Baba_Actors[Name->GetTile()].push_back(Name.get());
	return Name;
}

std::shared_ptr<ActiveWord> APlayGameMode::SpawnActive(TilePoint _Tile, std::string_view _Str)
{
	std::string Name = UEngineString::ToUpper(_Str);
	ActiveState* Astate = nullptr;
	if (Name._Equal("PUSH")) {
		Astate = &BabaUpdateHelper::Push;
	}
	else if (Name._Equal("MOVE")) {
		Astate = &BabaUpdateHelper::Move;
	}
	else if (Name._Equal("STOP")) {
		Astate = &BabaUpdateHelper::Stop;
	}
	else if (Name._Equal("PULL")) {
		Astate = &BabaUpdateHelper::Pull;
	}
	else if (Name._Equal("HOT")) {
		Astate = &BabaUpdateHelper::Hot;
	}
	else if (Name._Equal("FLOAT")) {
		Astate = &BabaUpdateHelper::Float;
	}
	else if (Name._Equal("SINK")) {
		Astate = &BabaUpdateHelper::Sink;
	}
	else if (Name._Equal("WIN")) {
		Astate = &BabaUpdateHelper::Win;
	}
	else if (Name._Equal("DEFEAT")) {
		Astate = &BabaUpdateHelper::Defeat;
	}
	else if (Name._Equal("YOU")) {
		Astate = &BabaUpdateHelper::You;
	}
	else if (Name._Equal("MELT")) {
		Astate = &BabaUpdateHelper::Melt;
	}
	else if (Name._Equal("OPEN")) {
		Astate = &BabaUpdateHelper::Open;
	}
	else if (Name._Equal("SHUT")) {
		Astate = &BabaUpdateHelper::Shut;
	}
	else {
		MsgBoxAssert("ActiveName에 이상한거넣었음");
	}


	std::shared_ptr<ActiveWord> Active = GetWorld()->SpawnActor<ActiveWord>("Active");
	Active->SetOrder(1);
	Active->StateInit(BabaState::IsActive);
	Active->SetBabaLocation(_Tile);
	Active->SetAnimation(Name);
	Active->SetActive(*Astate);


	Baba_Actors[Active->GetTile()].push_back(Active.get());
	return Active;
}

std::shared_ptr<ABabaBase> APlayGameMode::SpawnBaba(TilePoint _Tile, std::string_view _Str)
{
	std::string Name = UEngineString::ToUpper(_Str);
	std::shared_ptr<ABabaBase> Baba = nullptr;
	if (Name._Equal("BABA")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("BABA");
		Baba->StateInit(BabaState::IsBaba);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("WALL")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("WALL");
		Baba->StateInit(BabaState::IsWall);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("ROCK")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("ROCK");
		Baba->StateInit(BabaState::IsRock);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("FLAG")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("FLAG");
		Baba->StateInit(BabaState::IsFlag);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("SKULL")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("SKULL");
		Baba->StateInit(BabaState::IsSkull);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("WATER")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("WATER");
		Baba->StateInit(BabaState::IsWater);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("LAVA")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("LAVA");
		Baba->StateInit(BabaState::IsLava);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("GRASS")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("GRASS");
		Baba->StateInit(BabaState::IsGrass);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("ICE")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("ICE");
		Baba->StateInit(BabaState::IsIce);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("ALGAE")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("ALGAE");
		Baba->StateInit(BabaState::IsAlgae);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("BOX")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("BOX");
		Baba->StateInit(BabaState::IsBox);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("DOOR")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("DOOR");
		Baba->StateInit(BabaState::IsDoor);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("CRAB")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("CRAB");
		Baba->StateInit(BabaState::IsCrab);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("JELLY")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("JELLY");
		Baba->StateInit(BabaState::IsJelly);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("PILLAR")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("PILLAR");
		Baba->StateInit(BabaState::IsPillar);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("KEY")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("KEY");
		Baba->StateInit(BabaState::IsKey);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else if (Name._Equal("STAR")) {
		Baba = GetWorld()->SpawnActor<ABabaBase>("STAR");
		Baba->StateInit(BabaState::IsStar);
		Baba->SetBabaLocation(_Tile, 'D');
		Baba_Actors[Baba->GetTile()].push_back(Baba.get());
	}
	else {
		MsgBoxAssert("ActiveName에 이상한거넣었음");
	}
	return Baba;
}

std::shared_ptr<BottomTile> APlayGameMode::SpawnTile(TilePoint _Tile)
{
	std::shared_ptr<BottomTile> Tile = GetWorld()->SpawnActor<BottomTile>("Tile");
	Tile->SetActorLocation(FVector{ _Tile.X * 32, _Tile.Y * 32, 0 });
	return Tile;
}

void APlayGameMode::ContainerReset()
{
	//std::map <TilePoint, std::list<ABabaBase*>> Baba_Actors;
	//std::vector<ABabaBase*> Change_Baba;
	//std::vector<IsWord*> Is_Vec;
	//std::vector<AndWord*> And_Vec;
	//std::vector<HasWord*> Has_Vec;
	//std::stack<char> Stack_Input;

	Baba_Actors.clear();
	Change_Baba.clear();
	Is_Vec.clear();
	And_Vec.clear();
	Has_Vec.clear();
	while (Stack_Input.empty() != true) {
		Stack_Input.pop();
	}
}



