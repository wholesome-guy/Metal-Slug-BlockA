#pragma once
class Camera
{
public:
	Camera(int screenWidth, int screenHeight)
	{
		_screenWidth = screenWidth;
		_screenHeight = screenHeight;
	}

	void Follow(float2 targetPos);

	float2 GetPosition() { return _position; }

	int2 WorldToScreen(float2 worldPosition)
	{
		return { (int)(worldPosition.x - _position.x), (int)(worldPosition.y - _position.y) };
	}

private:
	float2 _position{ 0.0f, 0.0f };
	int _screenWidth =320, _screenHeight =224;


	float _xOffset = 0.25f;
	float _deadZoneHalfWidth = 40.f; 
	bool _hasBounds = false;
	float _minX = 0, _maxX = 0;
};

