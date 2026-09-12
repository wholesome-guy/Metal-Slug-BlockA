
#include "precomp.h"
#include "game.h"
#include <iostream>
#include "Player.h"
#include "Level.h"
#include "Camera.h"
#include "CollisionDetection.h"
#include "Debug.h"
#include "TesstObject.h"

void Game::Init()
{
	InitObjects();
}

void Game::Tick(float  deltaTime)
{
	Input();
	Update(deltaTime);
	Render();

}
void Game::Shutdown()
{
	delete _player;
	delete _level;
	delete _camera;
	delete _collision;
}
void Game::KeyDown(int input)
{
	if (input == GLFW_KEY_D)
	{
		_keyD = true;
	}
	else if (input == GLFW_KEY_A)
	{
		_keyA = true;
	}

	if (input == GLFW_KEY_S)
	{
		_keyS = true;
	}

	if (input == GLFW_KEY_SPACE)
	{
		_player->Jump();
	}

	//if (input == GLFW_KEY_RIGHT) _player->SetHitBoxOffset(1, 0);
	//if (input == GLFW_KEY_LEFT) _player->SetHitBoxOffset(-1, 0);
	//if (input == GLFW_KEY_UP) _player->SetHitBoxOffset(0, 1);
	//if (input == GLFW_KEY_DOWN) _player->SetHitBoxOffset(0, -1);
	//if (input == GLFW_KEY_ENTER) std::cout << _player->GetHitboxOffset().x << " , " << _player->GetHitboxOffset().y << std::endl;


	UpdateMovementInput();
}
void Game::MouseDown(int input)
{
	if (input == GLFW_MOUSE_BUTTON_1)
	{
		_player->Shoot();
	}
}
void Game::KeyUp(int input)
{
	if (input == GLFW_KEY_D)
	{
		_keyD = false;
	}
	else if (input == GLFW_KEY_A)
	{
		_keyA = false;
	}

	if (input == GLFW_KEY_S)
	{
		_keyS = false;
	}
	UpdateMovementInput();

}
void Game::InitObjects()
{
	_debug = new Debug();
	_player = new Player();
	_level = new Level();
	_camera = new Camera(SCRWIDTH, SCRHEIGHT);
	_collision = new CollisionDetection();
	_to = new TesstObject();

	_collision->SetPlayer(_player);
	_collision->SetLevel(_level);
	_collision->SetTestObject(_to);
}
void Game::Update(float deltatime)
{
	_collision->Update(deltatime);

	_player->Update(deltatime);

	_camera->Follow(_player->GetPosition());

}
void Game::Render()
{
	screen->Clear(0);

	_level->Render(screen, _camera);

	_to->Render(screen, _camera);

	_player->Render(screen, _camera);


	if (DEBUG)
	{
		_debug->DrawBoxDebug(screen, _camera, _player->GetHitboxPosition(), _player->GetHitboxSize(), 0x00ff00);


		_camera->DrawDebug(screen, _player->GetPosition());

		for (int i = 0; i < 20000; i++)
		{
			_debug->DrawBoxDebug(screen, _camera, _level->GetTile(i).position, _level->GetTile(i).size, _level->GetTile(i).color);
		}

		for (int i = 0; i < _collision->GetTileCount(); i++)
		{
			_debug->DrawBoxDebug(screen, _camera, _collision->GetTile(i).position, _collision->GetTile(i).size, 0x00ff00);
		}
	}
}
void Game::Input()
{
	_player->SetInputs(_movementInput);
}
void Game::UpdateMovementInput()
{
	_movementInput.x = (_keyD ? 1.f : 0.f) - (_keyA ? 1.f : 0.f);

	_movementInput.y = (_keyS ? -1.f : 0.f);
}




