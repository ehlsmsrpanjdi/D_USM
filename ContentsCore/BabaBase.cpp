#include "PreCompile.h"
#include "Bababase.h"
#include <EngineCore/Renderer.h>
#include <EngineCore/SpriteRenderer.h>


ABabaBase::ABabaBase()
{
	Renderer = CreateDefaultSubObject<USpriteRenderer>("Renderer");
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
	switch (BabaInput)
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
}

void ABabaBase::PopLerpMove()
{
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

	std::string AnimationName = "";
	if (Info.Who == BabaObject::Baba) {
		AnimationName.append("Baba_");
		AnimationName.append(InputToButton(BabaInput) + "_");
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
}

