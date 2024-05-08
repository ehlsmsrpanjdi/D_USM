#include "PreCompile.h"
#include "JellyGameMode.h"
#include "EngineCore/Camera.h"
#include "ContentsHelper.h"
#include "TileMap.h"
#include "Selector.h"
#include "JellySelectMap.h"
#include "StageBox.h"

JellyGameMode::JellyGameMode()
{
}

JellyGameMode::~JellyGameMode()
{
}

StageBox* JellyGameMode::SpawnStage(int _X, int _Y, std::string_view _Stage)
{
	std::shared_ptr<StageBox> box = GetWorld()->SpawnActor<StageBox>("Box");
	Stage.push_back(box.get());
	box->SetActorLocation(FVector{ _X * 32.f, _Y * 32.f });
	box->SetStageNum(_Stage);
	box->Tile = TilePoint(_X, _Y);
	return box.get();
}

void JellyGameMode::LevelEnd(ULevel* _NextLevel)
{
	int a = 0;
}

void JellyGameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0, 0, -100));

	ContentsHelper::WordInit();
	TileMap::TileSet(30, 30);

	std::shared_ptr<Selector> SelectorActor = GetWorld()->SpawnActor<Selector>("Select");
	SelectorActor->CurGameMode = this;
	std::shared_ptr<JellySelectMap> Map = GetWorld()->SpawnActor<JellySelectMap>("Map");
	StageBox* Box0 = SpawnStage(-8, -7, "00");
	StageBox* Box1 = SpawnStage(-7, -5, "01");
	StageBox* Box2 = SpawnStage(-7, -4, "02");
	StageBox* Box3 = SpawnStage(-6, -5, "03");
	StageBox* Box4 = SpawnStage(-6, -4, "04");
	StageBox* Box5 = SpawnStage(-7, -3, "05");
	StageBox* Box6 = SpawnStage(-5, -4, "06");
	StageBox* Box7 = SpawnStage(-6, -3, "07");

	Box0->NextStage.push_back(Box1);
	Box1->NextStage.push_back(Box2);
	Box1->NextStage.push_back(Box3);
	Box2->NextStage.push_back(Box4);
	Box2->NextStage.push_back(Box5);
	Box3->NextStage.push_back(Box4);
	Box5->NextStage.push_back(Box7);
	Box4->NextStage.push_back(Box7);
	Box4->NextStage.push_back(Box6);
	Box0->SetActive(true);
	SelectorActor->SetBabaLocation(-8, -7);
}

