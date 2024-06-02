#include "PreCompile.h"
#include "SelectGameMode.h"
#include "EngineCore/Camera.h"
#include "ContentsHelper.h"
#include "TileMap.h"
#include "Selector.h"
#include "SelectMap.h"
#include "StageBox.h"
#include "BackBackGround.h"

SelectGameMode::SelectGameMode()
{
}

SelectGameMode::~SelectGameMode()
{
}

StageBox* SelectGameMode::SpawnNextStage(int _X, int _Y, std::string_view _Stage)
{
	std::shared_ptr<StageBox> box = GetWorld()->SpawnActor<StageBox>("Box");
	Stage.push_back(box.get());
	box->SetActorLocation(FVector{ _X * 32.f, _Y * 32.f });
	box->SetNextStage(_Stage);
	box->Tile = TilePoint(_X, _Y);
	return box.get();
}

StageBox* SelectGameMode::SpawnStage(int _X, int _Y, std::string_view _Stage)
{
	std::shared_ptr<StageBox> box = GetWorld()->SpawnActor<StageBox>("Box");
	Stage.push_back(box.get());
	box->SetActorLocation(FVector{ _X * 32.f, _Y * 32.f });
	box->SetStageNum(_Stage);
	box->LRRenderTrue();
	box->Tile = TilePoint(_X, _Y);
	return box.get();
}

StageBox* SelectGameMode::SpawnLine(int _X, int _Y, bool _Right, bool _Up, bool _Left, bool _Down)
{
	std::shared_ptr<StageBox> box = GetWorld()->SpawnActor<StageBox>("Box");
	box->SetLine(_Right, _Up, _Left, _Down);
	box->RenderTrue();
	box->SetActorLocation(FVector{ _X * 32.f, _Y * 32.f });
	box->Tile = TilePoint(_X, _Y);
	return box.get();
}

void SelectGameMode::LevelEnd(ULevel* _NextLevel)
{
	int a = 0;
}

void SelectGameMode::LevelStart(ULevel* _PrevLevel)
{
	ContentsHelper::WordReset();
}

void SelectGameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0, 0, -100));

	ContentsHelper::WordInit();
	TileMap::TileSet(30, 30);

	std::shared_ptr<Selector> SelectorActor = GetWorld()->SpawnActor<Selector>("Select");
	SelectorActor->CurGameMode = this;
	std::shared_ptr<SelectMap> Map = GetWorld()->SpawnActor<SelectMap>("Map");
	std::shared_ptr<BackBackGround> BackGroundMap = GetWorld()->SpawnActor<BackBackGround>("BackGround");
	StageBox* Box0 = SpawnStage(-8, -7, "00");
	StageBox* Box1 = SpawnStage(-7, -5, "01");
	StageBox* Box2 = SpawnStage(-7, -4, "02");
	StageBox* Box3 = SpawnStage(-6, -5, "03");
	StageBox* Box4 = SpawnStage(-6, -4, "04");
	StageBox* Box5 = SpawnStage(-7, -3, "05");
	StageBox* Box6 = SpawnStage(-5, -4, "06");
	StageBox* Box7 = SpawnStage(-6, -3, "07");

	StageBox* Box08 = SpawnStage(-1, 0, "08");
	StageBox* Box09 = SpawnStage(-1, 1, "09");
	StageBox* Box10 = SpawnStage(-1, 2, "10");
	StageBox* Box11 = SpawnStage(0, 0, "11");
	StageBox* Box12 = SpawnStage(0, 1, "12");
	StageBox* Box13 = SpawnStage(0, 2, "13");
	StageBox* Box14 = SpawnStage(0, -1, "14");

	StageBox* LineBox1 = SpawnLine(-7, -6, 0, 1, 0, 1);
	StageBox* LineBox2 = SpawnLine(-7, -7, 0, 1, 1, 0);
	StageBox* LineBox3 = SpawnLine(-5, -5, 0, 1, 1, 0);

	StageBox* LineBox4 = SpawnLine(-5, -3, 1, 0, 1, 1);
	StageBox* LineBox5 = SpawnLine(-4, -3, 1, 0, 1, 0);
	StageBox* LineBox6 = SpawnLine(-3, -3, 1, 0, 1, 0);
	StageBox* LineBox7 = SpawnLine(-2, -3, 1, 0, 1, 0);
	StageBox* LineBox8 = SpawnLine(-1, -3, 0, 1, 1, 0);
	StageBox* LineBox9 = SpawnLine(-1, -2, 0, 1, 0, 1);
	StageBox* LineBox10 = SpawnLine(-1, -1, 0, 1, 0, 1);
	//Box0->NextStage.push_back(LineBox1);
	//Box0->NextStage.push_back(LineBox2);
	//Box3->NextStage.push_back(LineBox3);
	//Box7->NextStage.push_back(LineBox4);
	//Box7->NextStage.push_back(LineBox5);
	//Box7->NextStage.push_back(LineBox6);
	//Box7->NextStage.push_back(LineBox7);
	//Box7->NextStage.push_back(LineBox8);
	//Box7->NextStage.push_back(LineBox9);
	//Box7->NextStage.push_back(LineBox10);
	//Box7->NextStage.push_back(JellyStage);
	//
	//Box0->NextStage.push_back(Box1);
	//Box1->NextStage.push_back(Box2);
	//Box1->NextStage.push_back(Box3);
	//Box2->NextStage.push_back(Box4);
	//Box2->NextStage.push_back(Box5);
	//Box3->NextStage.push_back(Box4);
	//Box5->NextStage.push_back(Box7);
	//Box4->NextStage.push_back(Box7);
	//Box4->NextStage.push_back(Box6);
	//Box0->LRRenderTrue();
	SelectorActor->SetBabaLocation(-8, -7);
	InputOn();
}

void SelectGameMode::Tick(float _DeltaTime)
{
	Super::Tick(_DeltaTime);
	ContentsHelper::CoolTimeCheck(_DeltaTime);
	if (IsDown(VK_ESCAPE)) {
		GEngine->ChangeLevel("Title");
	}
}

