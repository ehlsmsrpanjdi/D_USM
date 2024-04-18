#pragma once
#include "BabaBase.h"
#include <EngineCore/EngineCore.h>
// Ό³Έν :
class ActiveWord : public ABabaBase
{

	GENERATED_BODY(AActor)
public:
	// constructor destructor
	ActiveWord();
	~ActiveWord();

	// delete Function
	ActiveWord(const ActiveWord& _Other) = delete;
	ActiveWord(ActiveWord&& _Other) noexcept = delete;
	ActiveWord& operator=(const ActiveWord& _Other) = delete;
	ActiveWord& operator=(ActiveWord&& _Other) noexcept = delete;

	ActiveState ActiveName;

	void BeginPlay() override;
	void Tick(float _DeltaTime) override;

	void SetActive(ActiveState _Info) {
		ActiveName = _Info;
	}

	void SetActive(bool _IsFloat, bool _IsPush, bool _IsMove) {
		ActiveName.IsFloat = _IsFloat;
		ActiveName.IsPush = _IsPush;
		ActiveName.IsMove = _IsMove;
	}

	ActiveState GetActive() {
		return ActiveName;
	}

	void SetAnimation(std::string_view _Str);



protected:

private:

};
