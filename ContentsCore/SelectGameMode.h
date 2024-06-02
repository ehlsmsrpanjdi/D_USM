#pragma once
#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"
#include "PlayGameMode.h"

class ABabaBase;
class StageBox;
class Selector;
// Ό³Έν :
class SelectGameMode : public APlayGameMode
{
	GENERATED_BODY(AGameMode)
	friend Selector;
public:
	// constructor destructor
	SelectGameMode();
	~SelectGameMode();

	// delete Function
	SelectGameMode(const SelectGameMode& _Other) = delete;
	SelectGameMode(SelectGameMode&& _Other) noexcept = delete;
	SelectGameMode& operator=(const SelectGameMode& _Other) = delete;
	SelectGameMode& operator=(SelectGameMode&& _Other) noexcept = delete;

	StageBox* SpawnNextStage(int _X, int _Y, std::string_view _Stage);
	StageBox* SpawnStage(int _X, int _Y, std::string_view _Stage);
	StageBox* SpawnLine(int _X, int _Y, bool _Right, bool _Up, bool _Left, bool _Down);
protected:
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _PrevLevel) override;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	std::vector<StageBox*> Stage = {nullptr,};
private:

};
