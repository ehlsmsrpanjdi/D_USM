#pragma once
#define MoveTime 1.f

// Ό³Έν :

struct BabaState {
	bool IsMove = false;
	bool IsBaba = false;
	bool IsPush = false;
};

class ContentsHelper
{
public:
	// constructor destructor
	ContentsHelper();
	~ContentsHelper();

	// delete Function
	ContentsHelper(const ContentsHelper& _Other) = delete;
	ContentsHelper(ContentsHelper&& _Other) noexcept = delete;
	ContentsHelper& operator=(const ContentsHelper& _Other) = delete;
	ContentsHelper& operator=(ContentsHelper&& _Other) noexcept = delete;

	static float Time;
	static void CoolTimeCheck(float _DeltaTime);

protected:

private:

};
