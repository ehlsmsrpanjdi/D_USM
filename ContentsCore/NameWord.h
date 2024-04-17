#pragma once
#include "BabaBase.h"
// Ό³Έν :
class NameWord : public ABabaBase
{
public:
	// constructor destructor
	NameWord();
	~NameWord();

	// delete Function
	NameWord(const NameWord& _Other) = delete;
	NameWord(NameWord&& _Other) noexcept = delete;
	NameWord& operator=(const NameWord& _Other) = delete;
	NameWord& operator=(NameWord&& _Other) noexcept = delete;

	void SetNameSet(BabaState _Word) {
		WordInfo = _Word;
	}
	BabaState GetNameSet() {
		return WordInfo;
	}

	BabaState WordInfo;
protected:

private:

};
