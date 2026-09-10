// Template, 2024 IGAD Edition
// Get the latest version from: https://github.com/jbikker/tmpl8
// IGAD/NHTV/BUAS/UU - Jacco Bikker - 2006-2024

#pragma once
class Player;
class Level;
class Camera;
class CollisionDetection;
class Debug;
namespace Tmpl8
{

class Game : public TheApp
{
public:
	// game flow methods
	void Init();
	void Tick( float deltaTime );
	void Shutdown();// { /* implement if you want to do something on exit */ }

	void MouseUp( int ) { /* implement if you want to detect mouse button presses */ }
	void MouseMove( int x, int y ) { mousePos.x = x, mousePos.y = y; }
	void MouseWheel( float ) { /* implement if you want to handle the mouse wheel */ }
	void MouseDown(int);
	void KeyUp(int); 
	void KeyDown(int);
	int2 mousePos = {0,0};
private:
	void Update(float deltatime);
	void Render();
	void Input();
	void InitObjects();

	void UpdateMovementInput();

	bool _keyD = false;
	bool _keyA = false;
	bool _keyS = false;

	float2 _movementInput = { 0,0 };
	Player* _player = nullptr;
	Level* _level = nullptr;
	Camera* _camera = nullptr;
	CollisionDetection* _collision = nullptr;
	Debug* _debug = nullptr;
};

} // namespace Tmpl8