#include "precomp.h"
#include "Camera.h"

void Camera::Follow(float2 targetPosition)
{
	float staticLineX = _screenWidth * _xOffset;

	float staticLineY = _screenHeight * _yOffset;

	float relativeX = targetPosition.x - _position.x;
	float relativeY = targetPosition.y - _position.y;

	float left = staticLineX - _deadZoneHalfWidth;
	float right = staticLineX + _deadZoneHalfWidth;

	float top = staticLineY - _deadZoneHalfHeight;

	if (relativeX < left)
	{
		_position.x -= (left - relativeX);
	}
	else if (relativeX > right)
	{
		_position.x += (relativeX - right);
	}

	if (relativeY < top)
	{
		_position.y -= (top - relativeY);
	}

	if (_hasBounds)
	{
		if (_position.x < _minX) _position.x = _minX;
		if (_position.x > _maxX - _screenWidth) _position.x = _maxX - _screenWidth;
	}

}

void Camera::DrawDebug(Tmpl8::Surface* screen, float2 targetPosition)
{
	float staticLineX = _screenWidth * _xOffset;
	float staticLineY = _screenHeight * _yOffset;

	int lineX = (int)staticLineX;
	int lineY = (int)staticLineY;

	// Vertical line at the horizontal follow trigger point
	screen->Line((float)lineX, 0, (float)lineX, (float)_screenHeight, 0xFF0000);

	// Horizontal line at the vertical follow trigger point
	screen->Line(0, (float)lineY, (float)_screenWidth, (float)lineY, 0xFF0000);

	// Deadzone box (green) — target position stays inside this box in screen space
	// before the camera starts moving
	int left = lineX - (int)_deadZoneHalfWidth;
	int right = lineX + (int)_deadZoneHalfWidth;
	int top = lineY - (int)_deadZoneHalfHeight;
	int bottom = lineY + (int)_deadZoneHalfHeight;

	screen->Line((float)left, (float)top, (float)right, (float)top, 0x00FF00);
	screen->Line((float)left, (float)bottom, (float)right, (float)bottom, 0x00FF00);
	screen->Line((float)left, (float)top, (float)left, (float)bottom, 0x00FF00);
	screen->Line((float)right, (float)top, (float)right, (float)bottom, 0x00FF00);

	// Where the target (player) actually is in screen space right now — blue cross
	int2 targetScreen = WorldToScreen(targetPosition);
	screen->Line((float)(targetScreen.x - 5), (float)targetScreen.y, (float)(targetScreen.x + 5), (float)targetScreen.y, 0x0000FF);
	screen->Line((float)targetScreen.x, (float)(targetScreen.y - 5), (float)targetScreen.x, (float)(targetScreen.y + 5), 0x0000FF);

	// Bounds (yellow), only meaningful in world space — draw at camera-relative screen position if you have them
	if (_hasBounds)
	{
		int minXScreen = (int)(_minX - _position.x);
		int maxXScreen = (int)(_maxX - _position.x);
		screen->Line((float)minXScreen, 0, (float)minXScreen, (float)_screenHeight, 0xFFFF00);
		screen->Line((float)maxXScreen, 0, (float)maxXScreen, (float)_screenHeight, 0xFFFF00);
	}
}


