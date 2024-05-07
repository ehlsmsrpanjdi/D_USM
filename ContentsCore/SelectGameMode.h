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

	void SpawnStage(int _X, int _Y, std::string_view _Stage);

protected:
	void BeginPlay() override;
	std::vector<StageBox*> Stage = {nullptr,};
private:

};
