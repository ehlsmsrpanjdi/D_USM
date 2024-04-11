#pragma once
#define MoveTime 1.f

// Ό³Έν :

struct float2D
{
	float x;
	float y;

	float2D operator*(const float& _Value) {
		float ResultX = x * _Value;
		float ResultY = y * _Value;
		return float2D{ ResultX,ResultY };
	}

	float2D operator+(const float2D& _Value) {
		float ResultX = x + _Value.x;
		float ResultY = y + _Value.y;
		return float2D{ ResultX,ResultY };
	}

	bool operator==(const float2D& _Value) {
		if (x == _Value.x && y == _Value.y) {
			return true;
		}
		else {
			return false;
		}
	}
};

struct TilePoint {
	union
	{
		struct
		{
			int X;
			int Y;
		};
		__int64 Location;
	};
};
enum class BabaObject {
	Baba,

};


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
