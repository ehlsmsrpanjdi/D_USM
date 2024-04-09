#pragma once
#include <EngineCore/GameMode.h>


class ABabaBase;
// Ό³Έν :
class APlayGameMode : public AGameMode
{
	GENERATED_BODY(AGameMode)

public:
	// constrcuter destructer
	APlayGameMode();
	~APlayGameMode();

	// delete Function
	APlayGameMode(const APlayGameMode& _Other) = delete;
	APlayGameMode(APlayGameMode&& _Other) noexcept = delete;
	APlayGameMode& operator=(const APlayGameMode& _Other) = delete;
	APlayGameMode& operator=(APlayGameMode&& _Other) noexcept = delete;

protected:
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	char Key = '0';
	std::vector<std::shared_ptr<ABabaBase>> Actors;
	bool IsInput = false;

	void ActorsMove();

private:
};

