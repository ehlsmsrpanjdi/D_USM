#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"

class Text;
// Ό³Έν :
class TitleGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)
public:
	// constructor destructor
	TitleGameMode();
	~TitleGameMode();

	// delete Function
	TitleGameMode(const TitleGameMode& _Other) = delete;
	TitleGameMode(TitleGameMode&& _Other) noexcept = delete;
	TitleGameMode& operator=(const TitleGameMode& _Other) = delete;
	TitleGameMode& operator=(TitleGameMode&& _Other) noexcept = delete;

protected:
	std::shared_ptr<Text> SpawnText(std::string_view _TextName);
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	Text* Selector = nullptr;
	float FadeTime = 0.0f;
	bool FadeOn = false;
private:
	int Select = 0;
};
