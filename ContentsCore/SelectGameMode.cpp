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
	SpawnStage(0, 5, "05");

	SelectorActor->SetBabaLocation(3, 3);
}

