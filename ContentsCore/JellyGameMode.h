#pragma once
#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"
#include "SelectGameMode.h"

class ABabaBase;
class StageBox;
class Selector;
// Ό³Έν :
class JellyGameMode : public SelectGameMode
{
	GENERATED_BODY(AGameMode)
	friend Selector;
public:
	// constructor destructor
	JellyGameMode();
	~JellyGameMode();

	// delete Function
	JellyGameMode(const JellyGameMode& _Other) = delete;
	JellyGameMode(JellyGameMode&& _Other) noexcept = delete;
	JellyGameMode& operator=(const JellyGameMode& _Other) = delete;
	JellyGameMode& operator=(JellyGameMode&& _Other) noexcept = delete;

	StageBox* SpawnStage(int _X, int _Y, std::string_view _Stage);

protected:
	void LevelEnd(ULevel* _NextLevel) override;
	void LevelStart(ULevel* _NextLevel) override;
	void BeginPlay() override;
	std::vector<StageBox*> Stage = { nullptr, };
private:

};
