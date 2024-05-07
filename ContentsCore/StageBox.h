#pragma once
#include "BabaBase.h"
#include "TileMap.h"
// Ό³Έν :
class StageBox : public AActor
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	StageBox();
	~StageBox();

	// delete Function
	StageBox(const StageBox& _Other) = delete;
	StageBox(StageBox&& _Other) noexcept = delete;
	StageBox& operator=(const StageBox& _Other) = delete;
	StageBox& operator=(StageBox&& _Other) noexcept = delete;

	std::string StageName = "00";

	void SetStageNum(std::string_view _Num);

	TilePoint Tile;

	TilePoint GetTile() {
		return Tile;
	}

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void NumRender();
	USpriteRenderer* LRenderer = nullptr;
	USpriteRenderer* RRenderer = nullptr;
private:

};
