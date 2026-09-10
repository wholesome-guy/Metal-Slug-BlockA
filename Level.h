#pragma once
#include <LDtkLoader/Project.hpp>
class Camera;

static const int _maxGridCount = 64;


struct CollisionTile {
	float2 position; 
	int2 size;
	uint color;
};
struct CollisionGrid {
	CollisionTile tiles[_maxGridCount];
	int count = 0;
};
class Level {

public:
	Level();
	virtual ~Level();
	void Render(Tmpl8::Surface* screen, Camera* camera);

	CollisionGrid ReturnCollisionGrid(float2 hitboxPos, int2 hitboxSize, int value);
	const CollisionTile& GetTile(int index) const { return _tiles[index]; }

private:

	void InitTiles();
	void VisualiseTiles();

	ldtk::Project _collisionTileMap;
	const ldtk::Layer* _collisionLayer = nullptr;

	int _gridCellSize = 0;
	int _gridRadius = 1;
	CollisionTile _tiles[20000] = {};

	Sprite* _map = nullptr;
	float2 _mapPosition = { 0, -80 };

};