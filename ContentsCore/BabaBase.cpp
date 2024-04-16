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

	BabaInput = '0';
	Renderer->ChangeAnimation("Baba_Right_1");

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
	switch (BabaInput)
	{
	case 'W':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y + 1 }) == true) {
			Move_Stack.push(true);
			NextLocation2D = Location2D + float2D{ 0.f, MoveLength };
			Info.Tile.Y += 1;
			CanMove = false;
		}
		else {
			Move_Stack.push(false);
		}
	}
	break;
	case 'A':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X - 1, Info.Tile.Y}) == true) {
			Move_Stack.push(true);
			NextLocation2D = Location2D + float2D{ -MoveLength, 0.f };
			Info.Tile.X -= 1;
			CanMove = false;
		}
		else {
			Move_Stack.push(false);
		}

	}
	break;
	case 'S':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y - 1 }) == true) {
			Move_Stack.push(true);
			NextLocation2D = Location2D + float2D{ 0.f, -MoveLength };
			Info.Tile.Y -= 1;
			CanMove = false;
		}
		else {
			Move_Stack.push(false);
		}

	}
	break;
	case 'D':
	{
		if (TileMap::TileMove(TilePoint{ Info.Tile.X + 1, Info.Tile.Y}) == true) {
			Move_Stack.push(true);
			NextLocation2D = Location2D + float2D{ MoveLength, 0.f };
			Info.Tile.X += 1;
			CanMove = false;
		}
		else {
			Move_Stack.push(false);
		}

	}
	break;
	default:
		break;
	}
	if (true == Move_Stack.top()) {
	IndexPlus(Info);
	InfoUpdate();
	}
}

void ABabaBase::PopLerpMove()
{
	bool IsMove = false;
	CanMove = false;
	if (Move_Stack.empty() != true) {
	IsMove = Move_Stack.top();
	Move_Stack.pop();
	}

	if (IsMove == false) {
		return;
	}

	PrevTile = Info.Tile;
	switch (BabaInput)
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
	_Info.AnimationIndex++;
	if (_Info.AnimationIndex >= 5) {
		_Info.AnimationIndex = 1;
	}
}

void ABabaBase::IndexMinus(BabaInfo& _Info)
{
	_Info.AnimationIndex--;
	if (_Info.AnimationIndex <= 0) {
		_Info.AnimationIndex = 4;
	}
}

void ABabaBase::InfoUpdate()
{
	char InputKey = BabaInput;
	if (Move_Stack.empty() == true) {
		InputKey = StartInput;
	}
	std::string AnimationName = "";
	if (Info.Who == BabaObject::Baba) {
		AnimationName.append("Baba_");
		AnimationName.append(InputToButton(InputKey) + "_");
		AnimationName.append(std::to_string(Info.AnimationIndex));
	}
	//AnimationName.
	Renderer->ChangeAnimation(AnimationName);
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

bool ABabaBase::BabaActiveCheck(char _Input)
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

bool ABabaBase::BabaCheck(char _Input, std::vector<ABabaBase*>& _Vec, std::map<__int64, std::list<ABabaBase*>>& _Map)
{
	StateCheck();
	if (false == PushCheck()) {
		IsChecked = true;
		CanMove = false;
		return false;
	}
	bool TempBool = true;
		switch (_Input)
		{
		case 'W':
		{
			if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y + 1 }) == true) {
				TilePoint Tile = TilePoint{ Info.Tile.X, Info.Tile.Y } + TilePoint{ 0, 1 };
				std::list<ABabaBase*>& _List = _Map[Tile.Location];
				if (_List.empty() == true) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
				for (ABabaBase*& Baba : _List) {
					bool Temp = Baba->BabaCheck(_Input, _Vec, _Map);
					TempBool = (TempBool && Temp);
				}
				if (true == TempBool) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
			}
		}
		break;
		case 'A':
		{
			if (TileMap::TileMove(TilePoint{ Info.Tile.X - 1, Info.Tile.Y }) == true) {
				TilePoint Tile = TilePoint{ Info.Tile.X, Info.Tile.Y } + TilePoint{ -1,0 };
				std::list<ABabaBase*>& _List = _Map[Tile.Location];
				if (true == _List.empty()) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
				for (ABabaBase*& Baba : _List) {
					bool Temp = Baba->BabaCheck(_Input, _Vec, _Map);
					TempBool = (TempBool && Temp);
				}
				if (true == TempBool) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
			}

		}
		break;
		case 'S':
		{
			if (TileMap::TileMove(TilePoint{ Info.Tile.X, Info.Tile.Y - 1 }) == true) {
				TilePoint Tile = TilePoint{ Info.Tile.X, Info.Tile.Y } + TilePoint{ 0, -1 };
				std::list<ABabaBase*>& _List = _Map[Tile.Location];
				if (true == _List.empty()) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
				for (ABabaBase*& Baba : _List) {
					bool Temp = Baba->BabaCheck(_Input, _Vec, _Map);
					TempBool = (TempBool && Temp);
				}
				if (true == TempBool) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
			}

		}
		break;
		case 'D':
		{
			if (TileMap::TileMove(TilePoint{ Info.Tile.X + 1, Info.Tile.Y }) == true) {
				TilePoint Tile = TilePoint{ Info.Tile.X, Info.Tile.Y } + TilePoint{ 1, 0 };
				std::list<ABabaBase*>& _List = _Map[Tile.Location];
				if (true == _List.empty()) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
				for (ABabaBase*& Baba : _List) {
					bool Temp = Baba->BabaCheck(_Input, _Vec, _Map);
					TempBool = (TempBool && Temp);
				}
				if (true == TempBool) {
					_Vec.push_back(this);
					CanMove = true;
					IsChecked = true;
					return true;
				}
			}
		}
		break;
		default:
			break;
		}
		CanMove = false;
		IsChecked = true;
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

void ABabaBase::StateCheck()
{
}

bool ABabaBase::MoveCheck()
{
	bool Temp = true;
	Temp = AState.IsMove && Temp;
	return Temp;
}

bool ABabaBase::PushCheck()
{
	switch (BState)
	{
	case BabaState::IsNone:
		break;
	case BabaState::IsBaba:
		
		break;
	case BabaState::IsRock:
		break;
	default:
		break;
	}
	bool Temp = true;
	Temp = AState.IsPush && Temp;
	return Temp;
}

void ABabaBase::StateInit(BabaState _State)
{
	BState = _State;
}

void ABabaBase::ActiveStateInit(ActiveState _State)
{
	AState = _State;
}
