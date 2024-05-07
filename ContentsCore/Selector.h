#pragma once
#include "BabaBase.h"
// Ό³Έν :

class SelectGameMode;

class Selector : public ABabaBase
{
	GENERATED_BODY(AActor)
	friend SelectGameMode;
public:
	// constructor destructor
	Selector();
	~Selector();

	// delete Function
	Selector(const Selector& _Other) = delete;
	Selector(Selector&& _Other) noexcept = delete;
	Selector& operator=(const Selector& _Other) = delete;
	Selector& operator=(Selector&& _Other) noexcept = delete;

protected:
	SelectGameMode* CurGameMode = nullptr;
	void BeginPlay() override;
	void Tick(float _DeltaTime) override;
	void Input();
	void StageCheck();
	char Key = '0';
	bool CanInput = true;
private:

};
