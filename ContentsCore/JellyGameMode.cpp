#include "PreCompile.h"
#include "JellyGameMode.h"
#include "EngineCore/Camera.h"
#include "ContentsHelper.h"
#include "TileMap.h"
#include "Selector.h"
#include "JellySelectMap.h"
#include "StageBox.h"
#include "JellyBackGround.h"
#include "BabaEditor.h"
#include "ContentsCore.h"


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
}

void JellyGameMode::LevelStart(ULevel* _NextLevel)
{
	InputOn();
	TileMap::TileSet(100, 100);

}

void JellyGameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0, 0, -100));
	Camera->AddActorLocation(FVector(32 * 40, 32 * 40));

	ContentsHelper::WordInit();

	std::shared_ptr<Selector> SelectorActor = GetWorld()->SpawnActor<Selector>("Select");
	SelectorActor->CurGameMode = this;
	SelectorActor->SetBabaLocation(35, 35);

	std::shared_ptr<JellySelectMap> JellyBack = GetWorld()->SpawnActor<JellySelectMap>("Jelly");
	std::shared_ptr<JellyBackGround> BackGroundMap = GetWorld()->SpawnActor<JellyBackGround>("BackGround");
	BackGroundMap->AddActorLocation(FVector(32 * 40, 32 * 40));
	JellyBack->AddActorLocation(FVector(32 * 40, 32 * 40));

	StageBox* PrevStage = SpawnNextStage(40, 33, "SelectGameLevel");
	PrevStage->RenderTrue();
	StageBox* Line1 = SpawnLine(40, 34, 0,1,0,1);
	Line1->RenderTrue();
	StageBox* Line2 = SpawnLine(40, 35, 0, 1, 0, 1);
	Line2->RenderTrue();

	StageBox* Box3 = SpawnStage(40, 36, "08");
	StageBox* Box4 = SpawnStage(40, 37, "09");
	StageBox* Box5 = SpawnStage(40, 38, "10");
	StageBox* Box6 = SpawnStage(39, 37, "11");
	StageBox* Box7 = SpawnStage(39, 38, "12");

	ContentsCore::Editor->GameMode = this;
	ContentsCore::Editor->Load("JellyStage");
	ContentsCore::Editor->Ignore();
}


