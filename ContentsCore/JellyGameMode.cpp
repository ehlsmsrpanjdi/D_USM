#include "PreCompile.h"
#include "JellyGameMode.h"
#include "EngineCore/Camera.h"
#include "ContentsHelper.h"
#include "TileMap.h"
#include "Selector.h"
#include "JellySelectMap.h"
#include "StageBox.h"
#include "JellyBackGround.h"
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
	int a = 0;
}

void JellyGameMode::LevelStart(ULevel* _NextLevel)
{
	ContentsCore::GameMode = this;
	InputOn();
}

void JellyGameMode::BeginPlay()
{
	Super::BeginPlay();
	std::shared_ptr<UCamera> Camera = GetWorld()->GetMainCamera();
	Camera->SetActorLocation(FVector(0, 0, -100));
	Camera->AddActorLocation(FVector(32 * 40, 32 * 40));

	ContentsHelper::WordInit();
	TileMap::TileSet(30, 30);

	std::shared_ptr<Selector> SelectorActor = GetWorld()->SpawnActor<Selector>("Select");
	SelectorActor->CurGameMode = this;
	SelectorActor->SetBabaLocation(35, 35);

	std::shared_ptr<JellySelectMap> JellyBack = GetWorld()->SpawnActor<JellySelectMap>("Jelly");
	std::shared_ptr<JellyBackGround> BackGroundMap = GetWorld()->SpawnActor<JellyBackGround>("BackGround");
	BackGroundMap->AddActorLocation(FVector(32 * 40, 32 * 40));
	JellyBack->AddActorLocation(FVector(32 * 40, 32 * 40));
}

