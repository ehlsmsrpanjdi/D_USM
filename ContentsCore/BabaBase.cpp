#include "PreCompile.h"
#include "Bababase.h"
#include "TileMap.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>
#include "FadeINEffect.h"
#include "Dust.h"
#include "ContentsHelper.h"

FVertexUV VertexUVValue;
FResultColorValue ColorData;
FCuttingData CuttingDataValue;


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
	BabaHelperUpdate();
	BabaUpdate();
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

//void ABabaBase::DebugMessageFunction()
//{
//	{
//		std::string Msg = std::format("PlayerPos : {}\n", std::to_string(Info.Tile.X) + "  " + std::to_string(Info.Tile.Y));
//		UEngineDebugMsgWindow::PushMsg(Msg);
//	}
//
//	{
//		std::string Msg = std::format("MousePos : {}\n", GetActorLocation().ToString());
//		UEngineDebugMsgWindow::PushMsg(Msg);
//	}
//}

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
	if (ContentsHelper::Time >= 1) {
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
			if (BState != BabaState::IsWall) {
				BState = BabaUpdateHelper::Wall;
			}
		}
		break;
		case BabaState::IsFlag:
		{
			if (BState != BabaState::IsFlag) {
				BState = BabaUpdateHelper::Flag;
			}
		}
		break;
		case BabaState::IsSkull:
		{
			if (BState != BabaState::IsSkull) {
				BState = BabaUpdateHelper::Skull;
			}
		}
		break;
		case BabaState::IsLava:
		{
			if (BState != BabaState::IsLava) {
				BState = BabaUpdateHelper::Lava;
			}
		}
		break;
		case BabaState::IsWater:
		{
			if (BState != BabaState::IsWater) {
				BState = BabaUpdateHelper::Water;
			}
		}
		break;
		}
	}
}
void ABabaBase::BabaUpdate()
{
	if (ContentsHelper::Time >= 1) {
		switch (BState)
		{
		case BabaState::IsNone:
			break;
		case BabaState::IsBaba:
		{
			Babachange();
		}
		break;
		case BabaState::IsWall:
		{
			//WallChange();
		}
		break;
		case BabaState::IsRock:
		{
			RockChange();
		}
		break;
		case BabaState::IsFlag:
			FlagChange();
			break;
		case BabaState::IsSkull:
			SkullChange();
			break;
		case BabaState::IsWater:
			//WaterChange();
			break;
		case BabaState::IsLava:
			//LavaChange();
			break;
		default:
			break;
		}
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

	Renderer->CreateAnimation("Wall0", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Lava0", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });
	Renderer->CreateAnimation("Water0", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 2, 20, 38 });

	Renderer->CreateAnimation("Wall1", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Lava1", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });
	Renderer->CreateAnimation("Water1", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 3, 21, 39 });

	Renderer->CreateAnimation("Wall2", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Lava2", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });
	Renderer->CreateAnimation("Water2", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 4, 22, 40 });

	Renderer->CreateAnimation("Wall3", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Lava3", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });
	Renderer->CreateAnimation("Water3", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 5, 23, 41 });

	Renderer->CreateAnimation("Wall4", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Lava4", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });
	Renderer->CreateAnimation("Water4", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 6, 24, 42 });

	Renderer->CreateAnimation("Wall5", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Lava5", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });
	Renderer->CreateAnimation("Water5", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 7, 25, 43 });

	Renderer->CreateAnimation("Wall6", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Lava6", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });
	Renderer->CreateAnimation("Water6", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 8, 26, 44 });

	Renderer->CreateAnimation("Wall7", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Lava7", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });
	Renderer->CreateAnimation("Water7", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 9, 27, 45 });

	Renderer->CreateAnimation("Wall8", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Lava8", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });
	Renderer->CreateAnimation("Water8", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{ 10, 28, 46 });

	Renderer->CreateAnimation("Wall9", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Lava9", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });
	Renderer->CreateAnimation("Water9", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{11, 29, 47 });

	Renderer->CreateAnimation("Wall10", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Lava10", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });
	Renderer->CreateAnimation("Water10", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{12, 30, 48 });

	Renderer->CreateAnimation("Wall11", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Lava11", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });
	Renderer->CreateAnimation("Water11", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{13, 31, 49 });

	Renderer->CreateAnimation("Wall12", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Lava12", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });
	Renderer->CreateAnimation("Water12", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{14, 32, 50 });

	Renderer->CreateAnimation("Wall13", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Lava13", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });
	Renderer->CreateAnimation("Water13", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{15, 33, 51 });

	Renderer->CreateAnimation("Wall14", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Lava14", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });
	Renderer->CreateAnimation("Water14", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{16, 34, 52 });;

	Renderer->CreateAnimation("Wall15", "Wall.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
	Renderer->CreateAnimation("Lava15", "Lava.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });
	Renderer->CreateAnimation("Water15", "Water.png", std::vector<float>{ 0.1f, 0.1f, 0.1f }, std::vector<int>{17, 35, 53 });

}

void ABabaBase::DustSpawn(char _Input)
{
	std::shared_ptr<Dust> DD = GetWorld()->SpawnActor<Dust>("Dust");
	DD->SetActorLocation(GetActorLocation());
	DD->SetReleaseLocation(_Input);
}

void ABabaBase::DeadRender()
{
	Renderer->SetActive(!Dead);
}

bool ABabaBase::RenderCheckHelper(std::map<TilePoint, std::list<ABabaBase*>>& _Map, TilePoint _Tile, BabaState _State)
{
	std::list<ABabaBase*>& _List = _Map[_Tile];
	if (_List.empty() == true) {
		return false;
	}
	for (ABabaBase* _Baba : _List) {
		if (_Baba->GetBstate() == _State) {
			return true;
		}
	}
	return false;
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
	default:
		return;
		break;
	}



}
