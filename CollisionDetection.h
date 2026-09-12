#pragma once
class Player;
class TesstObject;
class Camera;
#include "Level.h"
#include "tmpl8math.h"

const int _bitmapSize = 4096; //64 X 64


class CollisionDetection
{
public:
	CollisionDetection() = default;
	//virtual ~CollisionDetection();

	void Update(float deltatime);

	void SetPlayer(Player* player) { _player = player; }
	void SetLevel(Level* level) { _level = level; }
	void SetTestObject(TesstObject* object) { _object = object; }

	int GetTileCount()  { return _tileCount; }
	const CollisionTile& GetTile(int index) const { return _tiles[index]; }

private:

	CollisionTile _tiles[64] = {};
	int _tileCount = 0;

	Player* _player = nullptr;
	Level* _level = nullptr;
	TesstObject* _object = nullptr;

	bool AABBCheck(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB);
	float2 AABB(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB);
	float2 SlopeResolve(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB);

	bool PixelPerfect64(Sprite* spriteA, Sprite* spriteB, bool isColliding);

	void CollisionBroadPhase();
	void PlayerTileCollisions();

};

