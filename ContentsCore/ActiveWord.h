#pragma once
#include "BabaBase.h"
// Ό³Έν :
class ActiveWord : public ABabaBase
{
public:
	// constructor destructor
	ActiveWord();
	~ActiveWord();

	// delete Function
	ActiveWord(const ActiveWord& _Other) = delete;
	ActiveWord(ActiveWord&& _Other) noexcept = delete;
	ActiveWord& operator=(const ActiveWord& _Other) = delete;
	ActiveWord& operator=(ActiveWord&& _Other) noexcept = delete;

	ActiveInfo ActiveName;

	void SetActive(ActiveInfo _Info) {
		ActiveName = _Info;
	}

	void SetActive(bool _IsFloat, bool _IsPush, bool _IsMove) {
		ActiveName.IsFloat = _IsFloat;
		ActiveName.IsPush = _IsPush;
		ActiveName.IsMove = _IsMove;
	}

	ActiveInfo GetActive() {
		return ActiveName;
	}



protected:

private:

};
