#include "PreCompile.h"
#include "Bababase.h"
#include "TileMap.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "FadeINEffect.h"
#include "Dust.h"
#include "ContentsHelper.h"
#include "ContentsCore.h"

ABabaBase::ABabaBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	Renderer->SetAutoSize(1.5, true);
}

ABabaBase::~ABabaBase()
{
}

void ABabaBase::BeginPlay()
{
	Super::BeginPlay();

	RenderInit();
	BabaInput = '0';
}

void ABabaBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);

	DeadRender();
	SetActorlocation2D(Lerp(_DeltaTime));
	BabaUpdater();
	//DebugMessageFunction();
}

void ABabaBase::LerpMove()
{
	PrevTile = Info.Tile;
	if (CanMove == false) {
		Move_Stack.push(false);
		return;
	}

	KeyTileSet(BabaInput);

	if (true == Move_Stack.top()) {
		IndexPlus(Info);
		InfoUpdate();
	}
}

void ABabaBase::PopLerpMove()
{
	PrevStaticState();

	bool IsMove = false;
	if (Move_Stack.empty() != true) {
		IsMove = Move_Stack.top();
		Move_Stack.pop();
	}


	if (IsMove == false) {
		return;
	}

	KeyTileSetReverse(BabaInput);

	IndexMinus(Info);
	InfoUpdate();
}

float2D ABabaBase::Lerp(float _DeltaTime)
{
	if (ContentsHelper::Time < MoveTime) {
		return Location2D * (MoveTime - ContentsHelper::Time) + NextLocation2D * (ContentsHelper::Time);
	}
	else {
		Location2D = NextLocation2D;
		return Location2D;
	}
}

void ABabaBase::IndexPlus(BabaInfo& _Info)
{
	if (BState == BabaState::IsBaba) {
		_Info.AnimationIndex++;
		if (_Info.AnimationIndex >= 5) {
			_Info.AnimationIndex = 1;
		}
	}
}

void ABabaBase::IndexMinus(BabaInfo& _Info)
{
	if (BState == BabaState::IsBaba) {
		_Info.AnimationIndex--;
		if (_Info.AnimationIndex <= 0) {
			_Info.AnimationIndex = 4;
		}
	}
}

void ABabaBase::InfoUpdate()
{
	char InputKey = BabaInput;
	if (Move_Stack.empty() == true) {
		InputKey = StartInput;
	}
	else {
		if (Move_Stack.top() == false) {
			return;
		}
	}

	std::string AnimationName = "";
	if (BState == BabaState::IsBaba) {
		AnimationName.append("Baba_");
		AnimationName.append(InputToButton(InputKey) + "_");
		AnimationName.append(std::to_string(Info.AnimationIndex));
		Renderer->ChangeAnimation(AnimationName);
	}
}

std::string ABabaBase::InputToButton(char _Input)
{
	switch (_Input)
	{
	case 'W':
		return "Up";
		break;
	case 'A':
		return "Left";
		break;
	case 'S':
		return "Down";
		break;
	case 'D':
		return "Right";
		break;
	default:
		return "";
		MsgBoxAssert(std::to_string(_Input) + " 이 값은 도대체 왜 들어감??");
		break;
	}
}

bool ABabaBase::BabaMapCheck(char _Input)
{
	switch (_Input)
	{
	case 'W':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y + 1 }) == true) {
			return true;
		}
	}
	break;
	case 'A':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X - 1, Info.Tile.Y }) == true) {
			return true;
		}

	}
	break;
	case 'S':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y - 1 }) == true) {
			return true;
		}

	}
	break;
	case 'D':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X + 1, Info.Tile.Y }) == true) {
			return true;
		}
	}
	break;
	default:
		break;
	}
	return false;
}

void ABabaBase::ChangeTile(std::map<TilePoint, std::list<ABabaBase*>>& _Baba_Actors)
{
	if (GetPrevTile() != Info.Tile) {
		if (_Baba_Actors[GetPrevTile()].remove(this)) {
			_Baba_Actors[GetTile()].push_back(this);
		}
	}
}

bool ABabaBase::MoveCheck()
{
	if (true == GetDead()) {
		return false;
	}
	bool Temp = false;
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Temp = BabaUpdateHelper::ActiveBaba.IsMove || Temp;
		break;
	case BabaState::IsRock:
		Temp = BabaUpdateHelper::ActiveRock.IsMove || Temp;
		break;
	case BabaState::IsWall:
		Temp = BabaUpdateHelper::ActiveWall.IsMove || Temp;
		break;
	case BabaState::IsFlag:
		Temp = BabaUpdateHelper::ActiveFlag.IsMove || Temp;
		break;
	case BabaState::IsSkull:
		Temp = BabaUpdateHelper::ActiveSkull.IsMove || Temp;
		break;
	case BabaState::IsWater:
		Temp = BabaUpdateHelper::ActiveWater.IsMove || Temp;
		break;
	case BabaState::IsLava:
		Temp = BabaUpdateHelper::ActiveLava.IsMove || Temp;
		break;
	case BabaState::IsGrass:
		Temp = BabaUpdateHelper::ActiveGrass.IsMove || Temp;
		break;
	case BabaState::IsIce:
		Temp = BabaUpdateHelper::ActiveIce.IsMove || Temp;
		break;
	case BabaState::IsAlgae:
		Temp = BabaUpdateHelper::ActiveAlgae.IsMove || Temp;
		break;
	case BabaState::IsBox:
		Temp = BabaUpdateHelper::ActiveBox.IsMove || Temp;
		break;
	case BabaState::IsDoor:
		Temp = BabaUpdateHelper::ActiveDoor.IsMove || Temp;
		break;
	case BabaState::IsCrab:
		Temp = BabaUpdateHelper::ActiveCrab.IsMove || Temp;
		break;
	case BabaState::IsJelly:
		Temp = BabaUpdateHelper::ActiveJelly.IsMove || Temp;
		break;
	case BabaState::IsPillar:
		Temp = BabaUpdateHelper::ActivePillar.IsMove || Temp;
		break;
	case BabaState::IsKey:
		Temp = BabaUpdateHelper::ActiveKey.IsMove || Temp;
		break;
	case BabaState::IsStar:
		Temp = BabaUpdateHelper::ActiveStar.IsMove || Temp;
		break;

	default:
		break;
	}

	return Temp;

}

bool ABabaBase::PushCheck()
{
	bool Temp = false;
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Temp = BabaUpdateHelper::ActiveBaba.IsPush || Temp;
		break;
	case BabaState::IsRock:
		Temp = BabaUpdateHelper::ActiveRock.IsPush || Temp;
		break;
	case BabaState::IsWall:
		Temp = BabaUpdateHelper::ActiveWall.IsPush || Temp;
		break;
	case BabaState::IsFlag:
		Temp = BabaUpdateHelper::ActiveFlag.IsPush || Temp;
		break;
	case BabaState::IsSkull:
		Temp = BabaUpdateHelper::ActiveSkull.IsPush || Temp;
		break;
	case BabaState::IsWater:
		Temp = BabaUpdateHelper::ActiveWater.IsPush || Temp;
		break;
	case BabaState::IsLava:
		Temp = BabaUpdateHelper::ActiveLava.IsPush || Temp;
		break;
	case BabaState::IsGrass:
		Temp = BabaUpdateHelper::ActiveGrass.IsPush || Temp;
		break;
	case BabaState::IsIce:
		Temp = BabaUpdateHelper::ActiveIce.IsPush || Temp;
		break;
	case BabaState::IsAlgae:
		Temp = BabaUpdateHelper::ActiveAlgae.IsPush || Temp;
		break;
	case BabaState::IsBox:
		Temp = BabaUpdateHelper::ActiveBox.IsPush || Temp;
		break;
	case BabaState::IsDoor:
		Temp = BabaUpdateHelper::ActiveDoor.IsPush || Temp;
		break;
	case BabaState::IsCrab:
		Temp = BabaUpdateHelper::ActiveCrab.IsPush || Temp;
		break;
	case BabaState::IsJelly:
		Temp = BabaUpdateHelper::ActiveIce.IsPush || Temp;
		break;
	case BabaState::IsPillar:
		Temp = BabaUpdateHelper::ActivePillar.IsPush || Temp;
		break;
	case BabaState::IsKey:
		Temp = BabaUpdateHelper::ActiveKey.IsPush || Temp;
		break;
	case BabaState::IsStar:
		Temp = BabaUpdateHelper::ActiveStar.IsPush || Temp;
		break;
	case BabaState::IsWord:
		Temp = true;
		break;
	case BabaState::IsIs:
		Temp = true;
		break;
	case BabaState::IsActive:
		Temp = true;
		break;
	default:
		break;
	}

	return Temp;
}

bool ABabaBase::StopCheck()
{
	bool Temp = false;
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Temp = BabaUpdateHelper::ActiveBaba.IsStop || Temp;
		break;
	case BabaState::IsRock:
		Temp = BabaUpdateHelper::ActiveRock.IsStop || Temp;
		break;
	case BabaState::IsWall:
		Temp = BabaUpdateHelper::ActiveWall.IsStop || Temp;
		break;
	case BabaState::IsFlag:
		Temp = BabaUpdateHelper::ActiveFlag.IsStop || Temp;
		break;
	case BabaState::IsSkull:
		Temp = BabaUpdateHelper::ActiveSkull.IsStop || Temp;
		break;
	case BabaState::IsWater:
		Temp = BabaUpdateHelper::ActiveWater.IsStop || Temp;
		break;
	case BabaState::IsLava:
		Temp = BabaUpdateHelper::ActiveLava.IsStop || Temp;
		break;
	case BabaState::IsGrass:
		Temp = BabaUpdateHelper::ActiveGrass.IsStop || Temp;
		break;
	case BabaState::IsIce:
		Temp = BabaUpdateHelper::ActiveIce.IsStop || Temp;
		break;
	case BabaState::IsAlgae:
		Temp = BabaUpdateHelper::ActiveAlgae.IsStop || Temp;
		break;
	case BabaState::IsBox:
		Temp = BabaUpdateHelper::ActiveBox.IsStop || Temp;
		break;
	case BabaState::IsDoor:
		Temp = BabaUpdateHelper::ActiveDoor.IsStop || Temp;
		break;
	case BabaState::IsCrab:
		Temp = BabaUpdateHelper::ActiveCrab.IsStop || Temp;
		break;
	case BabaState::IsJelly:
		Temp = BabaUpdateHelper::ActiveIce.IsStop || Temp;
		break;
	case BabaState::IsPillar:
		Temp = BabaUpdateHelper::ActivePillar.IsStop || Temp;
		break;
	case BabaState::IsKey:
		Temp = BabaUpdateHelper::ActiveKey.IsStop || Temp;
		break;
	case BabaState::IsStar:
		Temp = BabaUpdateHelper::ActiveStar.IsStop || Temp;
		break;
	default:
		break;
	}

	return Temp;
}

void ABabaBase::StateInit(BabaState _State)
{
	BState = _State;
}

bool ABabaBase::BabaMoveCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	if (MoveCheck() == false) {
		return false;
	}
	if (BabaMapCheck(_Input) == false) {
		return false;
	}

	if (true == GetDead()) {
		return false;
	}

	TilePoint TempTile = KeyTileReturn(_Input);

	if (true == BabaNextTileCheck(_Map, TempTile)) {
		DustSpawn(_Input);
		_Vec.push_back(this);
		CanMove = true;
		IsChecked = true;
		return true;
	}

	bool CheckBool = true;
	std::list<ABabaBase*>& _List = _Map[TempTile];
	for (ABabaBase*& Baba : _List) {
		bool Check = Baba->BabaPushCheck(_Input, _Vec, _Map);
		CheckBool = (CheckBool && Check);
	}
	if (true == CheckBool) {
		DustSpawn(_Input);
		_Vec.push_back(this);
		CanMove = true;
		IsChecked = true;
		return true;
	}
	else {
		CanMove = false;
		IsChecked = true;
		return false;
	}
	CanMove = false;
	IsChecked = true;
	return false;
}

bool ABabaBase::BabaPushCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	if (StopCheck() == true) {
		IsChecked = true;
		CanMove = false;
		return false;
	}

	if (true == GetDead()) {
		IsChecked = true;
		CanMove = false;
		return true;
	}

	if (MoveCheck() == false) {
		if (false == PushCheck()) {
			IsChecked = true;
			CanMove = false;
			return true;
		}
	}

	if (false == BabaMapCheck(_Input)) {
		IsChecked = true;
		CanMove = false;
		return false;
	}

	TilePoint TempTile = KeyTileReturn(_Input);

	if (true == BabaNextTileCheck(_Map, TempTile)) {
		DustSpawn(_Input);
		_Vec.push_back(this);
		CanMove = true;
		IsChecked = true;
		return true;
	}

	else {
		bool TempBool = true;
		std::list<ABabaBase*>& _List = _Map[TempTile];
		for (ABabaBase*& Baba : _List) {
			bool Temp = Baba->BabaPushCheck(_Input, _Vec, _Map);
			TempBool = (TempBool && Temp);
		}
		if (true == TempBool) {
			DustSpawn(_Input);
			_Vec.push_back(this);
			CanMove = true;
			IsChecked = true;
			return true;
		}
		else {
			CanMove = false;
			IsChecked = true;
			return false;
		}
	}
}

bool ABabaBase::BabaNextTileCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
	if (_List.empty() == true) {
		return true;
	}
	else
		return false;
}

TilePoint ABabaBase::KeyTileReturn(char _Input)
{
	TilePoint TempTile = GetTile();
	switch (_Input)
	{
	case 'W':
	{
		TempTile.Y += 1;
	}
	break;
	case 'A':
	{
		TempTile.X -= 1;
	}
	break;
	case 'S':
	{
		TempTile.Y -= 1;
	}
	break;
	case 'D':
	{
		TempTile.X += 1;
	}
	break;
	default:
		break;
	}
	return TempTile;
}

void ABabaBase::KeyTileSet(char _Input)
{
	switch (_Input)
	{
	case 'W':
	{
		NextLocation2D = Location2D + float2D{ 0.f, MoveLength };
		Info.Tile.Y += 1;
	}
	break;
	case 'A':
	{
		NextLocation2D = Location2D + float2D{ -MoveLength, 0.f };
		Info.Tile.X -= 1;
	}
	break;
	case 'S':
	{
		NextLocation2D = Location2D + float2D{ 0.f, -MoveLength };
		Info.Tile.Y -= 1;
	}
	break;
	case 'D':
	{
		NextLocation2D = Location2D + float2D{ MoveLength, 0.f };
		Info.Tile.X += 1;
	}
	break;
	default:
		break;
	}
	Move_Stack.push(true);

}

void ABabaBase::KeyTileSetReverse(char _Input)
{
	PrevTile = Info.Tile;
	switch (_Input)
	{
	case 'W':
	{
		NextLocation2D = Location2D + float2D{ 0.f, -MoveLength };
		Info.Tile.Y -= 1;
	}
	break;
	case 'A':
	{
		NextLocation2D = Location2D + float2D{ MoveLength, 0.f };
		Info.Tile.X += 1;
	}
	break;
	case 'S':
	{
		NextLocation2D = Location2D + float2D{ 0.f, MoveLength };
		Info.Tile.Y += 1;
	}
	break;
	case 'D':
	{
		NextLocation2D = Location2D + float2D{ -MoveLength, 0.f };
		Info.Tile.X -= 1;
	}
	break;
	default:
		break;
	}
}

void ABabaBase::BabaHelperUpdate()
{
	switch (BState)
	{
	case BabaState::IsBaba:
	{
		if (BState != BabaUpdateHelper::Baba) {
			BState = BabaUpdateHelper::Baba;
		}
	}
	break;
	case BabaState::IsRock:
	{
		if (BState != BabaUpdateHelper::Rock) {
			BState = BabaUpdateHelper::Rock;
		}
	}
	break;
	case BabaState::IsWall:
	{
		if (BState != BabaUpdateHelper::Wall) {
			BState = BabaUpdateHelper::Wall;
		}
	}
	break;
	case BabaState::IsFlag:
	{
		if (BState != BabaUpdateHelper::Flag) {
			BState = BabaUpdateHelper::Flag;
		}
	}
	break;
	case BabaState::IsSkull:
	{
		if (BState != BabaUpdateHelper::Skull) {
			BState = BabaUpdateHelper::Skull;
		}
	}
	break;
	case BabaState::IsLava:
	{
		if (BState != BabaUpdateHelper::Lava) {
			BState = BabaUpdateHelper::Lava;
		}
	}
	break;
	case BabaState::IsWater:
	{
		if (BState != BabaUpdateHelper::Water) {
			BState = BabaUpdateHelper::Water;
		}
	}
	break;
	case BabaState::IsGrass:
	{
		if (BState != BabaUpdateHelper::Grass) {
			BState = BabaUpdateHelper::Grass;
		}
	}
	break;
	case BabaState::IsIce:
	{
		if (BState != BabaUpdateHelper::Ice) {
			BState = BabaUpdateHelper::Ice;
		}
	}
	break;
	}
}
void ABabaBase::BabaUpdate()
{
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
	{
		Babachange();
		Renderer->SetOrder(5);
	}
	break;
	case BabaState::IsWall:
	{
		Renderer->SetOrder(0);
		//WallChange();
	}
	break;
	case BabaState::IsRock:
	{
		Renderer->SetOrder(1);
		RockChange();
	}
	break;
	case BabaState::IsFlag:
		Renderer->SetOrder(1);
		FlagChange();
		break;
	case BabaState::IsSkull:
		Renderer->SetOrder(0);
		SkullChange();
		break;
	case BabaState::IsWater:
		Renderer->SetOrder(0);
		//WaterChange();

		break;
	case BabaState::IsLava:
		Renderer->SetOrder(0);
		//LavaChange();
		break;
	case BabaState::IsGrass:
		Renderer->SetOrder(0);
		break;
	case BabaState::IsIce:
		Renderer->SetOrder(0);
		break;
	case BabaState::IsAlgae:
		AlgaeChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsBox:
		BoxChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsDoor:
		DoorChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsCrab:
		CrabChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsJelly:
		JellyChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsPillar:
		PillarChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsKey:
		KeyChange();
		Renderer->SetOrder(0);
		break;
	case BabaState::IsStar:
		StarChange();
		Renderer->SetOrder(0);
		break;
	default:
		break;
	}
}

void ABabaBase::BabaUpdater()
{
	BabaHelperUpdate();
	BabaUpdate();
	int Size = Move_Stack.size();
	if (Move_Stack_Size == Size) {
		return;
	}
	else {
		Move_Stack_Size = Size;
		Type_Stack.push(static_cast<int>(BState));
	}
}



void ABabaBase::RockChange()
{
	Renderer->ChangeAnimation("RockObj");
}

void ABabaBase::FlagChange()
{
	Renderer->ChangeAnimation("FlagObj");
}

void ABabaBase::SkullChange()
{
	Renderer->ChangeAnimation("SkullObj");
}

void ABabaBase::WaterChange()
{
	Renderer->ChangeAnimation("Water0");
}

void ABabaBase::LavaChange()
{
	Renderer->ChangeAnimation("Lava0");
}

void ABabaBase::WallChange()
{
	Renderer->ChangeAnimation("Wall0");
}

void ABabaBase::AlgaeChange()
{
	Renderer->ChangeAnimation("AlgaeObj");
}

void ABabaBase::BoxChange()
{
	Renderer->ChangeAnimation("BoxObj");
}

void ABabaBase::DoorChange()
{
	Renderer->ChangeAnimation("DoorObj");
}

void ABabaBase::CrabChange()
{
	Renderer->ChangeAnimation("CrabObj");
}

void ABabaBase::JellyChange()
{
	Renderer->ChangeAnimation("JellyObj");
}

void ABabaBase::PillarChange()
{
	Renderer->ChangeAnimation("PillarObj");
}

void ABabaBase::KeyChange()
{
	Renderer->ChangeAnimation("KeyObj");
}

void ABabaBase::StarChange()
{
	Renderer->ChangeAnimation("StarObj");
}

void ABabaBase::Babachange()
{
	InfoUpdate();
}

void ABabaBase::RenderInit()
{
	Renderer->SetOrder(1);
	Renderer->SetMaterial("2DImage");


	Renderer->CreateAnimation("Baba_Down_1", "Baba_Down_1.png", 0.1f);
	Renderer->CreateAnimation("Baba_Down_2", "Baba_Down_2.png", 0.1f);
	Renderer->CreateAnimation("Baba_Down_3", "Baba_Down_3.png", 0.1f);
	Renderer->CreateAnimation("Baba_Down_4", "Baba_Down_4.png", 0.1f);
	Renderer->CreateAnimation("Baba_Right_1", "Baba_Right_1.png", 0.1f);
	Renderer->CreateAnimation("Baba_Right_2", "Baba_Right_2.png", 0.1f);
	Renderer->CreateAnimation("Baba_Right_3", "Baba_Right_3.png", 0.1f);
	Renderer->CreateAnimation("Baba_Right_4", "Baba_Right_4.png", 0.1f);
	Renderer->CreateAnimation("Baba_Left_1", "Baba_Left_1.png", 0.1f);
	Renderer->CreateAnimation("Baba_Left_2", "Baba_Left_2.png", 0.1f);
	Renderer->CreateAnimation("Baba_Left_3", "Baba_Left_3.png", 0.1f);
	Renderer->CreateAnimation("Baba_Left_4", "Baba_Left_4.png", 0.1f);
	Renderer->CreateAnimation("Baba_Up_1", "Baba_Up_1.png", 0.1f);
	Renderer->CreateAnimation("Baba_Up_2", "Baba_Up_2.png", 0.1f);
	Renderer->CreateAnimation("Baba_Up_3", "Baba_Up_3.png", 0.1f);
	Renderer->CreateAnimation("Baba_Up_4", "Baba_Up_4.png", 0.1f);

	Renderer->CreateAnimation("FlagObj", "FlagObj.png", 0.1f);
	Renderer->CreateAnimation("RockObj", "RockObj.png", 0.1f);
	Renderer->CreateAnimation("SkullObj", "SkullObj.png", 0.1f);
	Renderer->CreateAnimation("DoorObj", "Door.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("AlgaeObj", "Algae.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("BoxObj", "Box.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("JellyObj", "Jelly.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("KeyObj", "Key.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("PillarObj", "Pillar.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("StarObj", "Star.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 5, 8});
	Renderer->CreateAnimation("CrabObj", "Crab.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{2, 8, 13});

	Renderer->CreateAnimation("ICE0", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("ICE1", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("ICE2", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("ICE3", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("ICE4", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("ICE5", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("ICE6", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("ICE7", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("ICE8", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("ICE9", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("ICE10", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("ICE11", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("ICE12", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("ICE13", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("ICE14", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("ICE15", "ICE.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });

	Renderer->CreateAnimation("Grass0", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Wall0", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Lava0", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Water0", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });

	Renderer->CreateAnimation("Grass1", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Wall1", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Lava1", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Water1", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });

	Renderer->CreateAnimation("Grass2", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Wall2", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Lava2", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Water2", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });

	Renderer->CreateAnimation("Grass3", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Wall3", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Lava3", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Water3", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });

	Renderer->CreateAnimation("Grass4", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Wall4", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Lava4", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Water4", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });

	Renderer->CreateAnimation("Grass5", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Wall5", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Lava5", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Water5", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });

	Renderer->CreateAnimation("Grass6", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Wall6", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Lava6", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Water6", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });

	Renderer->CreateAnimation("Grass7", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Wall7", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Lava7", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Water7", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });

	Renderer->CreateAnimation("Grass8", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Wall8", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Lava8", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Water8", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });

	Renderer->CreateAnimation("Grass9", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Wall9", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Lava9", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Water9", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });

	Renderer->CreateAnimation("Grass10", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Wall10", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Lava10", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Water10", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });

	Renderer->CreateAnimation("Grass11", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Wall11", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Lava11", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Water11", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });

	Renderer->CreateAnimation("Grass12", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Wall12", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Lava12", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Water12", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });

	Renderer->CreateAnimation("Grass13", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Wall13", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Lava13", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Water13", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });

	Renderer->CreateAnimation("Grass14", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Wall14", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Lava14", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Water14", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });;

	Renderer->CreateAnimation("Grass15", "Grass.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
	Renderer->CreateAnimation("Wall15", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
	Renderer->CreateAnimation("Lava15", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
	Renderer->CreateAnimation("Water15", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });

}

void ABabaBase::DustSpawn(char _Input)
{
	std::shared_ptr<Dust> DD = GetWorld()->SpawnActor<Dust>("Dust");
	DD->SetActorLocation(GetActorLocation());
	DD->SetReleaseLocation(_Input);
	DD->SetColor(BState);
}

void ABabaBase::DeadRender()
{
	Renderer->SetActive(!Dead);
	BabaState HasState = BabaUpdateHelper::StateToActive(BState).HasState;
	//if (HasState != BabaState::IsNone) {
	//	ContentsCore::GameMode
	//}
}

bool ABabaBase::RenderCheckHelper(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile, BabaState _State)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
	if (_List.empty() == true) {
		return false;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->GetBstate() == _State) {
			if (_Baba->Renderer->IsActive() == false) {
				continue;
			}
			return true;
		}
	}
	return false;
}

void ABabaBase::PrevStaticState()
{
	BabaState BBState;
	if (Type_Stack.empty() != true) {
		BBState = static_cast<BabaState>(Type_Stack.top());
		Type_Stack.pop();
	}
	else {
		return;
	}
	if (BBState != BState) {
		switch (BBState)
		{
		case BabaState::IsBaba:
			BabaUpdateHelper::Baba = BBState;
			break;
		case BabaState::IsWall:
			BabaUpdateHelper::Wall = BBState;
			break;
		case BabaState::IsRock:
			BabaUpdateHelper::Rock = BBState;
			break;
		case BabaState::IsFlag:
			BabaUpdateHelper::Flag = BBState;
			break;
		case BabaState::IsSkull:
			BabaUpdateHelper::Skull = BBState;
			break;
		case BabaState::IsWater:
			BabaUpdateHelper::Water = BBState;
			break;
		case BabaState::IsLava:
			BabaUpdateHelper::Lava = BBState;
			break;
		case BabaState::IsGrass:
			BabaUpdateHelper::Grass = BBState;
			break;
		case BabaState::IsIce:
			BabaUpdateHelper::Ice = BBState;
			break;
		case BabaState::IsAlgae:
			BabaUpdateHelper::Algae = BBState;
			break;
		case BabaState::IsBox:
			BabaUpdateHelper::Box = BBState;
			break;
		case BabaState::IsDoor:
			BabaUpdateHelper::Door = BBState;
			break;
		case BabaState::IsCrab:
			BabaUpdateHelper::Crab = BBState;
			break;
		case BabaState::IsJelly:
			BabaUpdateHelper::Jelly = BBState;
			break;
		case BabaState::IsPillar:
			BabaUpdateHelper::Pillar = BBState;
			break;
		case BabaState::IsKey:
			BabaUpdateHelper::Key = BBState;
			break;
		case BabaState::IsStar:
			BabaUpdateHelper::Star = BBState;
			break;

		default:
		{
			MsgBoxAssert("예외처리 안된 거 있는 것 같으니 수정 요망");
		}
		break;
		}
		BState = BBState;
	}
}

void ABabaBase::RenderCheck(std::map<TilePoint, std::list<ABabaBase*>>& _Map)
{
	TilePoint TileW = KeyTileReturn('W');
	TilePoint TileA = KeyTileReturn('A');
	TilePoint TileS = KeyTileReturn('S');
	TilePoint TileD = KeyTileReturn('D');
	// 1 , 2 , 4, 8  오 위 왼 아
	int index = 0;
	switch (BState)
	{
	case BabaState::IsWall:
	{
		if (RenderCheckHelper(_Map, TileD, BState)) {
			index += 1;
		}
		if (RenderCheckHelper(_Map, TileW, BState)) {
			index += 2;
		}
		if (RenderCheckHelper(_Map, TileA, BState)) {
			index += 4;
		}
		if (RenderCheckHelper(_Map, TileS, BState)) {
			index += 8;
		}
		Renderer->ChangeAnimation("Wall" + std::to_string(index));
	}
	break;
	case BabaState::IsWater:
	{
		if (RenderCheckHelper(_Map, TileD, BState)) {
			index += 1;
		}
		if (RenderCheckHelper(_Map, TileW, BState)) {
			index += 2;
		}
		if (RenderCheckHelper(_Map, TileA, BState)) {
			index += 4;
		}
		if (RenderCheckHelper(_Map, TileS, BState)) {
			index += 8;
		}
		Renderer->ChangeAnimation("Water" + std::to_string(index));
	}
	break;
	case BabaState::IsLava:
	{
		if (RenderCheckHelper(_Map, TileD, BState)) {
			index += 1;
		}
		if (RenderCheckHelper(_Map, TileW, BState)) {
			index += 2;
		}
		if (RenderCheckHelper(_Map, TileA, BState)) {
			index += 4;
		}
		if (RenderCheckHelper(_Map, TileS, BState)) {
			index += 8;
		}
		Renderer->ChangeAnimation("Lava" + std::to_string(index));
	}
	break;
	case BabaState::IsGrass:
	{
		if (RenderCheckHelper(_Map, TileD, BState)) {
			index += 1;
		}
		if (RenderCheckHelper(_Map, TileW, BState)) {
			index += 2;
		}
		if (RenderCheckHelper(_Map, TileA, BState)) {
			index += 4;
		}
		if (RenderCheckHelper(_Map, TileS, BState)) {
			index += 8;
		}
		Renderer->ChangeAnimation("Grass" + std::to_string(index));
	}
	break;
	case BabaState::IsIce:
	{
		if (RenderCheckHelper(_Map, TileD, BState)) {
			index += 1;
		}
		if (RenderCheckHelper(_Map, TileW, BState)) {
			index += 2;
		}
		if (RenderCheckHelper(_Map, TileA, BState)) {
			index += 4;
		}
		if (RenderCheckHelper(_Map, TileS, BState)) {
			index += 8;
		}
		Renderer->ChangeAnimation("Ice" + std::to_string(index));
	}
	break;
	default:
		return;
		break;
	}



}
