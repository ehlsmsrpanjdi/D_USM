#include "PreCompile.h"
#include "Selector.h"
#include <EngineCore/DefaultSceneComponent.h>
#include <EngineCore/SpriteRenderer.h>
#include "SelectGameMode.h"
#include "StageBox.h"
#include "ContentsCore.h"
#include "BabaEditor.h"
#include "BackGround.h"

Selector::Selector()
{

}

Selector::~Selector()
{
}

void Selector::BeginPlay()
{
	Super::BeginPlay();
	Renderer->SetOrder(2);
	Renderer->SetMaterial("2DImage");

	Renderer->CreateAnimation("Selector", "SelectObj.png");
	Renderer->ChangeAnimation("Selector");
	BState = BabaState::IsNone;
	Renderer->SetAutoSize(1.0f, true);
	Renderer->SetScale(FVector(32.f, 32.f));
	InputOn();
}

void Selector::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	if (ContentsHelper::Time <= MoveTime) {
		CanInput = true;
	}
	if (CanInput == true) {
	Input();
	}
	SetActorlocation2D(Lerp(_DeltaTime));
}

void Selector::Input()
{
	if (CanInput == false) {
		return;
	}
	if (true == IsDown('A'))
	{
		Key = 'A';
		CanInput = false;
		ContentsHelper::Time = 0;
	}

	else if (true == IsDown('D'))
	{
		Key = 'D';
		CanInput = false;
		ContentsHelper::Time = 0;
	}

	else if (true == IsDown('W'))
	{
		Key = 'W';
		CanInput = false;
		ContentsHelper::Time = 0;
	}

	else if (true == IsDown('S'))
	{
		Key = 'S';
		CanInput = false;
		ContentsHelper::Time = 0;
	}

	else if (true == IsDown(VK_RETURN)) {
		StageCheck();
	}

	else {
		Key = '0';
		return;
	}

	KeyTileSet(Key);
}

void Selector::StageCheck()
{
	for (StageBox* Box : CurGameMode->Stage) {
		if (Box == nullptr) {
			continue;
		}
		TilePoint TempTile = Box->GetTile();

		BoxEnum Info = Box->GetBoxInfo();

		switch (Info)
		{
		case BoxEnum::Stage:
		{
			if (GetTile() == TempTile) {
				GEngine->ChangeLevel("PlayLevel");
				ContentsCore::Editor->Load("Stage" + Box->StageName);
				SizeChange(Box->StageName);
				Box->RenderOn();
			}
		}
			break;
		case BoxEnum::Map:
		{
			if (GetTile() == TempTile) {
				GEngine->ChangeLevel("JellySelectGameLevel");
			}
		}
			break;
		default:
			break;
		}
				
	}
}

void Selector::SizeChange(std::string_view _Str)
{
	if (_Str._Equal("00")) {
		BackGroundImage::Back->Size = FVector(12 * 16, 8 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(12 * 16, 8 * 16));
	}
	else if (_Str._Equal("01")) {
		BackGroundImage::Back->Size = FVector(16 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(16 * 16,14 * 16));
	}
	else if (_Str._Equal("02")) {
		BackGroundImage::Back->Size = FVector(16 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(16 * 16,14 * 16));
	}
	else if (_Str._Equal("03")) {
		BackGroundImage::Back->Size = float4(20 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(20 * 16,14 * 16));
	}
	else if (_Str._Equal("04")) {
		BackGroundImage::Back->Size = float4(20 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(20 * 16, 14 * 16));
	}
	else if (_Str._Equal("05")) {
		BackGroundImage::Back->Size = float4(20 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(20 * 16, 14 * 16));
	}
	else if (_Str._Equal("06")) {
		BackGroundImage::Back->Size = float4(20 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(20 * 16, 14 * 16));
	}
	else if (_Str._Equal("07")) {
		BackGroundImage::Back->Size = float4(20 * 16, 14 * 16);
		BackGroundImage::Back->AddRenderSize(FVector(20 * 16, 14 * 16));
	}
	else if (_Str._Equal("00")) {

	}
	else if (_Str._Equal("00")) {

	}
	else if (_Str._Equal("00")) {

	}
	else if (_Str._Equal("00")) {

	}
	else if (_Str._Equal("00")) {

	}
	else if (_Str._Equal("00")) {

	}
}
