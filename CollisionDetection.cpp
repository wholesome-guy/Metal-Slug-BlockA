#include "precomp.h"
#include "CollisionDetection.h"
#include "Player.h"
#include "Camera.h"


void CollisionDetection::Update(float deltatime)
{

	CollisionGrid groundGrid = _level->ReturnCollisionGrid(_player->GetHitboxPosition(), _player->GetHitboxSize(),1);
	_tileCount = groundGrid.count;

	for (int i = 0; i < groundGrid.count; i++)
	{
		_tiles[i] = groundGrid.tiles[i];
		float2 direction = AABB(_player->GetHitboxPosition(), _player->GetHitboxSize(), groundGrid.tiles[i].position, groundGrid.tiles[i].size);
		if (direction.x != 0 || direction.y != 0)
		{
			_player->Collision(direction,CollisionState::Ground);
		}
	}


	CollisionGrid oneWayGrid = _level->ReturnCollisionGrid(_player->GetHitboxPosition(), _player->GetHitboxSize(), 2);

	for (int i = 0; i < oneWayGrid.count; i++)
	{
		float2 direction = AABB(_player->GetHitboxPosition(), _player->GetHitboxSize(), oneWayGrid.tiles[i].position, oneWayGrid.tiles[i].size);
		if (direction.x != 0 || direction.y != 0)
		{
			_player->Collision(direction, CollisionState::OneWay);
		}
	}

	CollisionGrid slopeGrid = _level->ReturnCollisionGrid(_player->GetHitboxPosition(), _player->GetHitboxSize(), 3);

	for (int i = 0; i < slopeGrid.count; i++)
	{
		float2 direction = SlopeResolve(_player->GetHitboxPosition(), _player->GetHitboxSize(), slopeGrid.tiles[i].position, slopeGrid.tiles[i].size);

		_player->Collision(direction, CollisionState::Slope);

	}

}

float2 CollisionDetection::AABB(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB)
{

	if (sizeA.x == 0 || sizeA.y == 0|| sizeB.x == 0 || sizeB.y == 0) return { 0,0 };

	bool overlapping = ((positionA.x + sizeA.x >= positionB.x) && (positionA.x <= positionB.x + sizeB.x) && (positionA.y + sizeA.y >= positionB.y) && (positionA.y <= positionB.y + sizeB.y));
	if (!overlapping) return { 0,0 };

	float overlapLeft = positionA.x + sizeA.x - positionB.x;
	float overlapRight = positionB.x + sizeB.x - positionA.x;
	float overlapTop = positionA.y + sizeA.y - positionB.y;
	float overlapBottom = positionB.y + sizeB.y - positionA.y;

	float minOverlapX = std::min(overlapLeft, overlapRight);
	float minOverlapY = std::min(overlapTop, overlapBottom);

	if (minOverlapX < minOverlapY)
	{
		return (overlapLeft < overlapRight) ? float2{ -overlapLeft, 0 } : float2{ overlapRight, 0 };
	}
	else
	{
		return (overlapTop < overlapBottom) ? float2{ 0, -overlapTop } : float2{ 0, overlapBottom };
	}
}

float2 CollisionDetection::SlopeResolve(float2 positionA, int2 sizeA, float2 positionB, int2 sizeB)
{
	if (sizeA.x == 0 || sizeA.y == 0 || sizeB.x == 0 || sizeB.y == 0) return { 0,0 };

	bool overlapping = ((positionA.x + sizeA.x >= positionB.x) && (positionA.x <= positionB.x + sizeB.x) && (positionA.y + sizeA.y >= positionB.y) && (positionA.y <= positionB.y + sizeB.y));
	if (!overlapping) return { 0,0 };

	float objectABottom = positionA.y + sizeA.y;
	float objectBTop = positionB.y;

	float overlap = objectABottom - objectBTop;

	if (overlap > 0 && overlap <= sizeB.y)
	{
		return { 0, -overlap }; 
	}
}


