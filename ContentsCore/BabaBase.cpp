#include "PreCompile.h"
#include "Bababase.h"
#include "TileMap.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>
#include <EngineCore/DefaultSceneComponent.h>

ABabaBase::ABabaBase()
{
	UDefaultSceneComponent* Root = CreateDefaultSubObject<UDefaultSceneComponent>("Renderer");
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
	Renderer->SetupAttachment(Root);
	SetRoot(Root);
	InputOn();
}

ABabaBase::~ABabaBase()
{
}

void ABabaBase::BeginPlay()
{
	Super::BeginPlay();

	Renderer->SetAutoSize(1.5, true);
	float4 Location4D = GetActorLocation();
	Location2D.x = Location4D.X;
	Location2D.y = Location4D.Y;

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

	//Renderer->CreateAnimation("Wall", "Wall.png", std::vector<float>{ 0.1f }, std::vector<int>{ 2,4,5 });
	//Renderer->ChangeAnimation("wall");
	Renderer->SetSprite("Wall.png");

	BabaInput = '0';
	//Renderer->ChangeAnimation("Baba_Right_1");
	

}

void ABabaBase::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	SetActorlocation2D(Lerp(_DeltaTime));
	DebugMessageFunction();
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

void ABabaBase::DebugMessageFunction()
{
	{
		std::string Msg = std::format("PlayerPos : {}\n", std::to_string(Info.Tile.X) + "  " + std::to_string(Info.Tile.Y));
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	{
		std::string Msg = std::format("MousePos : {}\n", GetActorLocation().ToString());
		UEngineDebugMsgWindow::PushMsg(Msg);
	}

	//{
	//	std::string Msg = std::format("BabaIndex : {}\n", std::to_string());
	//	UEngineDebugMsgWindow::PushMsg(Msg);
	//}
}

void ABabaBase::ChangeTile(std::map<__int64, std::list<ABabaBase*>>& _Baba_Actors)
{
	if (GetPrevTile64() != Info.Tile.Location) {
		if (_Baba_Actors[GetPrevTile64()].remove(this)) {
			_Baba_Actors[GetTile64()].push_back(this);
		}
	}
}

bool ABabaBase::MoveCheck()
{

	bool Temp = true;
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Temp = BabaUpdateHelper::ActiveBaba.IsMove && Temp;
		break;
	case BabaState::IsRock:
		Temp = BabaUpdateHelper::ActiveRock.IsMove && Temp;
		break;
	default:
		break;
	}

	return Temp;

}

bool ABabaBase::PushCheck()
{
	bool Temp = true;
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		Temp = BabaUpdateHelper::ActiveBaba.IsPush && Temp;
		break;
	case BabaState::IsRock:
		Temp = BabaUpdateHelper::ActiveRock.IsPush && Temp;
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

bool ABabaBase::BabaMoveCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	if (MoveCheck() == false) {
		return false;
	}
	if (BabaMapCheck(_Input) == false) {
		return false;
	}

	TilePoint TempTile = KeyTileReturn(_Input);

	if (true == BabaNextTileCheck(_Map, TempTile)) {
		_Vec.push_back(this);
		CanMove = true;
		IsChecked = true;
		return true;
	}

	bool CheckBool = true;
	std::list<ABabaBase*>& _List = _Map[TempTile.Location];
	for (ABabaBase*& Baba : _List) {
		bool Check = Baba->BabaPushCheck(_Input, _Vec, _Map);
		CheckBool = (CheckBool && Check);
	}
	if (true == CheckBool) {
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

bool ABabaBase::BabaPushCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<__int64, std::list<ABabaBase*>>& _Map)
{

	if (false == PushCheck()) {
		IsChecked = true;
		CanMove = false;
		return false;
	}

	if (false == BabaMapCheck(_Input)) {
		IsChecked = true;
		CanMove = false;
		return false;
	}

	TilePoint TempTile = KeyTileReturn(_Input);

	if (true == BabaNextTileCheck(_Map, TempTile)) {
		_Vec.push_back(this);
		CanMove = true;
		IsChecked = true;
		return true;
	}

	else {
		bool TempBool = true;
		std::list<ABabaBase*>& _List = _Map[TempTile.Location];
		for (ABabaBase*& Baba : _List) {
			bool Temp = Baba->BabaPushCheck(_Input, _Vec, _Map);
			TempBool = (TempBool && Temp);
		}
		if (true == TempBool) {
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

bool ABabaBase::BabaNextTileCheck(std::map<__int64, std::list<ABabaBase*>>& _Map, TilePoint _Tile)
{
	std::list<ABabaBase*>& _List = _Map[_Tile.Location];
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
