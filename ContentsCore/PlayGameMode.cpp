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

APlayGameMode::APlayGameMode()
{
	ContentsCore::GameMode = this;
}

APlayGameMode::~APlayGameMode()
{}

void APlayGameMode::BeginPlay()
{
	Super::BeginPlay();

	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(320.0f, 160.0f, -100.0f));

	ContentsHelper::WordInit();
	TileMap::TileSet(10, 10);

	InputOn();
}

void APlayGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
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

	if (IsPress('Q')) {
		ContentsHelper::FadeEffectOut(GetWorld());
	}

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
			WinCheck();
			DefeatCheck();
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
							break;
						}
					}
				}
			}
		}
	}
}

void APlayGameMode::WinCheck()
{
	for (std::pair<const TilePoint, std::list<ABabaBase*>>& Iter : Baba_Actors)
	{
		std::list<ABabaBase*>& BabaBase = Iter.second;
		for (ABabaBase*& _BabaBase : BabaBase) {
			if (GetActive(_BabaBase->GetBstate()).IsWin == true) {
				TilePoint Tile = _BabaBase->GetTile();
				for (ABabaBase*& _Baba : Baba_Actors[Tile]) {
					if (true == BabaUpdateHelper::StateToActive(_Baba->GetBstate()).IsYou) {
						int a = 0;
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
	std::map <TilePoint, std::list<ABabaBase*>> Baba_Actors1;
	std::vector<ABabaBase*> Change_Baba1;
	std::vector<IsWord*> Is_Vec1;
	std::vector<AndWord*> And_Vec1;
	std::stack<char> Stack_Input1;

	Baba_Actors.clear();
	Change_Baba.clear();
	Is_Vec.clear();
	And_Vec.clear();
	while (Stack_Input.empty() != true) {
		Stack_Input.pop();
	}
}



