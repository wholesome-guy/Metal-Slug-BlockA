#pragma once
class Player;
class TesstObject;
#include "Level.h"
class Camera;
class CollisionDetection
{
public:
	CollisionDetection() = default;
	//virtual ~CollisionDetection();

	void Update(float deltatime);

	void SetPlayer(Player* player) { _player = player; }
	void SetLevel(Level* level) { _level = level; }


	int GetTileCount()  { return _tileCount; }
	const CollisionTile& GetTile(int index) const { return _tiles[index]; }

private:

	CollisionTile _tiles[64] = {};
	int _tileCount = 0;

	Player* _player = nullptr;
	Level* _level = nullptr;


	float2 AABB(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB);
	float2 SlopeResolve(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB);

	void CollisionBroadPhase();
	void PlayerTileCollisions();

};

