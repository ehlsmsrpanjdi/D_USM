#pragma once
#define MoveTime 1.f
#define MoveLength 32.f
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


	TilePoint operator+(TilePoint& _Point) {
		int TempX = X + _Point.X;
		int TempY = Y + _Point.Y;
		return TilePoint{ TempX, TempY };
	}

	TilePoint operator+(TilePoint _Point) {
		int TempX = X + _Point.X;
		int TempY = Y + _Point.Y;
		return TilePoint{TempX, TempY};
	}

};

enum class BabaState {
	IsNone = 0,
	IsBaba,
	IsRock,
	IsWord,
	IsActive,
	IsIs,
};

enum class WordInfo {

};

struct ActiveInfo {
	bool IsFloat = false;
	bool IsPush = false;
	bool IsMove = false;
};

struct ActiveState {
	ActiveState() {
		bool IsFloat = false;
		bool IsPush = false;
		bool IsMove = false;
	}
	ActiveState(bool _a, bool _b, bool _c) {
		IsFloat = _a;
		IsPush = _b;
		IsMove = _c;
	}
	bool IsFloat = false;
	bool IsPush = false;
	bool IsMove = false;

	BabaState ChangeState = BabaState::IsNone;
};

class BabaUpdateHelper {
public:
	static ActiveState ActiveBaba;
	static ActiveState ActiveRock;


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
