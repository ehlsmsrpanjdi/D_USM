#pragma once
#include "BabaBase.h"
// Ό³Έν :
class NameWord : public ABabaBase
{
	GENERATED_BODY(AActor)
public:
	// constructor destructor
	NameWord();
	~NameWord();

	// delete Function
	NameWord(const NameWord& _Other) = delete;
	NameWord(NameWord&& _Other) noexcept = delete;
	NameWord& operator=(const NameWord& _Other) = delete;
	NameWord& operator=(NameWord&& _Other) noexcept = delete;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	BabaState WordInfo = BabaState::IsWord;
	void SetNameSet(BabaState _Word) {
		WordInfo = _Word;
	}
	BabaState GetNameSet() {
		return WordInfo;
	}

protected:

private:

};
