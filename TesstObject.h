#pragma once

class Camera;
class TesstObject
{
public:
	TesstObject();
	void Collision(bool);
	void Render(Tmpl8::Surface* screen, Camera* camera);
	float2 _position = { 200, 120 };


	float2 GetHitBox() { return { _position.x + _hitboxOffset.x,_position.y + _hitboxOffset.y }; }
	int2 GetHitBoxSize() { return { _hitboxWidth,_hitboxHeight }; }


	Sprite* _sprite = nullptr;
	int _width;
	int _height;
	uint* _originalPixels = nullptr;

	float2 _hitboxOffset = { 16, 25 }; 
	int _hitboxWidth = 32;
	int _hitboxHeight = 32;
};

