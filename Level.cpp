#include "precomp.h"
#include "Level.h"
#include "Camera.h"
#include <iostream>

Level::Level()
{
	_map = new Sprite(new Surface("assets/Level.png"), 1);

	InitTiles();
}

Level::~Level()
{
	delete _map;
}


void Level::Render(Tmpl8::Surface* screen, Camera* camera)
{
	int2 mapScreenPos = camera->WorldToScreen(_mapPosition);
	_map->Draw(screen, mapScreenPos.x, mapScreenPos.y);
}

void Level::InitTiles()
{
	_collisionTileMap.loadFromFile("assets/Level.ldtk");

	_collisionLayer = &_collisionTileMap.getWorld().getLevel("Level_0").getLayer("IntGrid");
	_gridCellSize = _collisionLayer->getCellSize();

	VisualiseTiles();
}



CollisionGrid Level::ReturnCollisionGrid(float2 hitboxPosition, int2 hitboxSize, int value)
{

	CollisionGrid tileGrid;
	tileGrid.count = 0;

	float2 topLeft = hitboxPosition;
	float2 bottomRight = { hitboxPosition.x + hitboxSize.x, hitboxPosition.y + hitboxSize.y };

	int2 topLeftGridPosition = { static_cast<int>((topLeft.x - _mapPosition.x) / _gridCellSize),static_cast<int>((topLeft.y - _mapPosition.y) / _gridCellSize)};
	int2 bottomRightGridPosition = { static_cast<int>((bottomRight.x - _mapPosition.x) / _gridCellSize),static_cast<int>((bottomRight.y - _mapPosition.y) / _gridCellSize) };

	int2 minGrid = { topLeftGridPosition.x - _gridRadius,topLeftGridPosition.y - _gridRadius };
	int2 maxGrid = { bottomRightGridPosition.x + _gridRadius,bottomRightGridPosition.y + _gridRadius};

	int2 gridSize = { _collisionLayer->getGridSize().x, _collisionLayer->getGridSize().y };

	for (int i = minGrid.x; i <= maxGrid.x; i++)
	{
		for (int j = minGrid.y; j <= maxGrid.y; j++)
		{
			if (i < 0 || j < 0 || i >= gridSize.x || j >= gridSize.y)
				continue;

			if (value == static_cast<int>(_collisionLayer->getIntGridVal(i, j).value))
			{

				CollisionTile tile;
				tile.position = {
					i * static_cast<float>(_gridCellSize) + _mapPosition.x,
					j * static_cast<float>(_gridCellSize) + _mapPosition.y
				};
				tile.size = { _gridCellSize, _gridCellSize };
				tileGrid.tiles[tileGrid.count] = tile;
				tileGrid.count++;
			}
		}
	}

	return tileGrid;


}

void Level::VisualiseTiles()
{
	int2 gridSize = { _collisionLayer->getGridSize().x, _collisionLayer->getGridSize().y };

	for (int i = 0, c =0; i < gridSize.x; i++)
	{
		for (int j = 0; j < gridSize.y; j++, c++)
		{
			int value = static_cast<int>(_collisionLayer->getIntGridVal(i, j).value);

			uint color;
			if (value == 1)
				color = 0x000000;
			else if (value == 2)
				color = 0xff0000;
			else if (value == 3) color = 0x0000ff;
			else
				continue; 

			float2 worldPos = {
				i * static_cast<float>(_gridCellSize) + _mapPosition.x,
				j * static_cast<float>(_gridCellSize) + _mapPosition.y
			};
			int2 size = { _gridCellSize, _gridCellSize };

			CollisionTile tile;
			tile.color = color;
			tile.position = worldPos;
			tile.size = size;
			_tiles[c] = tile;

		

		}
	}
}

