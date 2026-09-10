#include "precomp.h"
#include "Camera.h"

void Camera::Follow(float2 targetPosition)
{
	float staticLineX = _screenWidth * _xOffset;

	float relativeX = targetPosition.x - _position.x;

	float left = staticLineX - _deadZoneHalfWidth;
	float right = staticLineX + _deadZoneHalfWidth;

	if (relativeX < left)
	{
		_position.x -= (left - relativeX);
	}
	else if (relativeX > right)
	{
		_position.x += (relativeX - right);
	}

	//if (_hasBounds)
	//{
	//	if (_position.x < _minX) _position.x = _minX;
	//	if (_position.x > _maxX - _screenWidth) _position.x = _maxX - _screenWidth;
	//}

}


