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

	bool operator==(const TilePoint& _Other) const {
		if (X == _Other.X && Y == _Other.Y) {
			return true;
		}
		return false;
	}
};

enum class BabaState {
	IsNone = 0,
	IsBaba,
	IsWall,
	IsRock,
	IsFlag,
	IsSkull,
	IsWater,
	IsLava,
	IsGrass,	
	IsIce,
	IsWord,
	IsActive,
	IsIs,
	IsAnd,
};

struct ActiveState {

	bool IsFloat = false;
	bool IsPush = false;
	bool IsMove = false;
	bool IsStop = false;
	bool IsPull = false;
	bool IsWin = false;
	bool IsDefeat = false;
	bool IsHot = false;
	bool IsSink = false;
	bool IsYou = false;
	bool IsMelt = false;
};

class BabaUpdateHelper {
public:
	static ActiveState ActiveBaba;
	static ActiveState ActiveRock;
	static ActiveState ActiveWord;
	static ActiveState ActiveWall;
	static ActiveState ActiveSkull;
	static ActiveState ActiveFlag;
	static ActiveState ActiveWater;
	static ActiveState ActiveLava;
	static ActiveState ActiveGrass;
	static ActiveState ActiveIce;


	static ActiveState None;
	static ActiveState Float;
	static ActiveState Push;
	static ActiveState Move;
	static ActiveState Stop;
	static ActiveState Pull;
	static ActiveState Win;
	static ActiveState Defeat;
	static ActiveState Hot;
	static ActiveState Sink;
	static ActiveState You;
	static ActiveState Melt;

	static BabaState Baba;
	static BabaState Wall;
	static BabaState Rock;
	static BabaState Flag;
	static BabaState Skull;
	static BabaState Water;
	static BabaState Lava;
	static BabaState Grass;
	static BabaState Ice;

	static ActiveState StateToActive(BabaState _State) {
		switch (_State)
		{
		case BabaState::IsBaba:
			return BabaUpdateHelper::ActiveBaba;
			break;
		case BabaState::IsWall:
			return BabaUpdateHelper::ActiveWall;
			break;
		case BabaState::IsRock:
			return BabaUpdateHelper::ActiveRock;
			break;
		case BabaState::IsFlag:
			return BabaUpdateHelper::ActiveFlag;
			break;
		case BabaState::IsSkull:
			return BabaUpdateHelper::ActiveSkull;
			break;
		case BabaState::IsWater:
			return BabaUpdateHelper::ActiveWater;
			break;
		case BabaState::IsLava:
			return BabaUpdateHelper::ActiveLava;
			break;
		case BabaState::IsGrass:
			return BabaUpdateHelper::ActiveGrass;
		case BabaState::IsIce:
			return BabaUpdateHelper::ActiveIce;
		case BabaState::IsWord:
		case BabaState::IsActive:
		case BabaState::IsIs:
		case BabaState::IsAnd:
			return BabaUpdateHelper::ActiveWord;
			break;
		default:
			break;
		}
	}

};

class FadeINEffect;
class FadeOUTEffect;
enum class Fade;

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
	static float EffectTime;
	static void CoolTimeCheck(float _DeltaTime);
	static void WordInit();
	static void FadeEffectIn(ULevel* _Level);
	static void FadeEffectOut(ULevel* _Level);
	static std::shared_ptr<FadeINEffect> FadeIn;
	static std::shared_ptr<FadeOUTEffect> FadeOut;
	static Fade FadeNum;

protected:

private:

};
