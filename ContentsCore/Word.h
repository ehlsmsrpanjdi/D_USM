#pragma once
#include "BabaBase.h"
#include <EngineCore/EngineCore.h>
// Ό³Έν :
class AWord : public ABabaBase
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	AWord();
	~AWord();

	

	// delete Function
	AWord(const AWord& _Other) = delete;
	AWord(AWord&& _Other) noexcept = delete;
	AWord& operator=(const AWord& _Other) = delete;
	AWord& operator=(AWord&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void WorldInit();
	void IsCheck();
protected:

private:

};
