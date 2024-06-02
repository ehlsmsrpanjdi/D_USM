#pragma once
#include "BabaBase.h"
#include "TileMap.h"
// Ό³Έν :

enum class BoxEnum {
	None,
	Stage,
	Line,
	Map,
};


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

	std::vector<StageBox*> NextStage = {};
	std::string MapName = "";
	void SetNextStage(std::string_view _StageName);
	void SetLine(bool _Right, bool _Up, bool _Left, bool _Down);
	void AnimationInit();
	std::string_view GetMapName() {
		return MapName;
	}

	void RenderTrue();
	void LRRenderTrue();
	bool IsClick = false;
	BoxEnum GetBoxInfo() {
		return BoxInfo;
	}


protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void NumRender();
	USpriteRenderer* LRenderer = nullptr;
	USpriteRenderer* RRenderer = nullptr;
	USpriteRenderer* Renderer = nullptr;
	BoxEnum BoxInfo = BoxEnum::None;
private:

};
