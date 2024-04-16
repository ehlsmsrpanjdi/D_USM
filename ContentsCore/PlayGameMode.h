#pragma once
#include <EngineCore/GameMode.h>
#include <stack>
#include "ContentsHelper.h"

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
	std::map <__int64, std::list<ABabaBase*>> Baba_Actors;
	std::vector<ABabaBase*> Change_Baba;
	//std::vector<std::shared_ptr<ABabaBase>> Baba_Actors;
	std::stack<char> Stack_Input;
	bool IsInput = false;
	int Count = 0;

	void Baba_Input();

	void Stack_Push(char _Key);
	void Stack_Pop();
	void Change_BabaPos();
	void BabaInputCheck();
	void DebugMessageFunction();
	
	void WordUpdate();

private:

	bool CanInput = false;
};

