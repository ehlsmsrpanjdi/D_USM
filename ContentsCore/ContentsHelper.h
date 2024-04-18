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

	TilePoint() { X = 0; Y = 0; }
	TilePoint(int _X, int _Y) {
		X = _X;
		Y = _Y;
	}

	TilePoint operator+(TilePoint& _Point) {
		int TempX = X + _Point.X;
		int TempY = Y + _Point.Y;
		return TilePoint{ TempX, TempY };
	}

	TilePoint operator+(TilePoint _Point) {
		int TempX = X + _Point.X;
		int TempY = Y + _Point.Y;
		return TilePoint{ TempX, TempY };
	}

	bool operator<(const TilePoint& _Other) const
	{
		if ((X < _Other.X)) {
			return true;
		}
		else if (X > _Other.X) {
			return false;
		}
		else {
			if (Y < _Other.Y) {
				return true;
			}
			else {
				return false;
			}

		}
	}

	bool operator!=(const TilePoint& _Other) const {
		if (X == _Other.X && Y == _Other.Y) {
			return false;
		}
		return true;
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

struct ActiveState {
	ActiveState() {
		IsFloat = false;
		IsPush = false;
		IsMove = false;
	}
	ActiveState(bool _a, bool _b, bool _c) {
		IsFloat = _a;
		IsPush = _b;
		IsMove = _c;
	}
	void operator=(ActiveState _Info) {
		IsFloat = _Info.IsFloat;
		IsMove = _Info.IsMove;
		IsPush = _Info.IsPush;
	}

	void InfoSet(ActiveState _Info) {
		IsFloat = IsFloat || _Info.IsFloat;
		IsMove = IsMove || _Info.IsMove;
		IsPush = IsPush || _Info.IsPush;
	}

	bool IsFloat = false;
	bool IsPush = false;
	bool IsMove = false;

};

class BabaUpdateHelper {
public:
	static ActiveState ActiveBaba;
	static ActiveState ActiveRock;
	static ActiveState ActiveWord;

	static ActiveState Push;
	static ActiveState Move;
	static ActiveState None;


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
