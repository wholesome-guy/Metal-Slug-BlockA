#pragma once
class Camera;
class Debug
{
public:
	void DrawBoxDebug(Tmpl8::Surface* screen, Camera* camera, float2 pos, int2 size, uint color);
};

