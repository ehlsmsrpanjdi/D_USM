#include "PreCompile.h"
#include "SelectGameMode.h"
#include "EngineCore/Camera.h"
#include "ContentsHelper.h"
#include "TileMap.h"
#include "Selector.h"
#include "SelectMap.h"
#include "StageBox.h"

SelectGameMode::SelectGameMode()
{
}

SelectGameMode::~SelectGameMode()
{
}

void SelectGameMode::SpawnStage(int _X, int _Y, std::string_view _Stage)
{
	std::shared_ptr<StageBox> box = GetWorld()->SpawnActor<StageBox>("Box");
	Stage.push_back(box.get());
	box->SetActorLocation(FVector{ _X * 32.f, _Y * 32.f });
	box->SetStageNum(_Stage);
	box->Tile = TilePoint(_X, _Y);
}

void SelectGameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0,0,-100));

	ContentsHelper::WordInit();
	TileMap::TileSet(30, 30);

	std::shared_ptr<Selector> SelectorActor = GetWorld()->SpawnActor<Selector>("Select");
	SelectorActor->CurGameMode = this;
	std::shared_ptr<SelectMap> Map = GetWorld()->SpawnActor<SelectMap>("Map");
	SpawnStage(-8, -7, "00");
	SpawnStage(-7, -5, "01");
	SpawnStage(-7, -4, "02");
	SpawnStage(-6, -5, "03");
	SpawnStage(-6, -4, "04");
	SpawnStage(-7, -3, "05");
	SpawnStage(-5, -4, "06");
	SpawnStage(-6, -3, "07");

	SelectorActor->SetBabaLocation(-8, -7);
}

