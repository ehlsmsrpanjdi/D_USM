#pragma once
#include "ContentsHelper.h"
struct TilePoint;
// Ό³Έν :
class TileMap
{
public:
	// constructor destructor
	TileMap();
	~TileMap();

	// delete Function
	TileMap(const TileMap& _Other) = delete;
	TileMap(TileMap&& _Other) noexcept = delete;
	TileMap& operator=(const TileMap& _Other) = delete;
	TileMap& operator=(TileMap&& _Other) noexcept = delete;

	static TilePoint Tile;

	static bool TileMove(TilePoint _NextTile) {
		bool CheckX = ((_NextTile.X > TileMap::Tile.X) || (_NextTile.X < 0));
		bool CheckY = ((_NextTile.Y > TileMap::Tile.Y) || (_NextTile.Y < 0));
		if ((CheckX || CheckY) == true) {
			return false;
		}
		else{
			return true;
		}
	}

	static void TileSet(int _X, int _Y) {
		TileMap::Tile.X = _X;
		TileMap::Tile.Y = _Y;
	}



protected:

private:

};
