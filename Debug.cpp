#include "precomp.h"
#include "Debug.h"
#include "Camera.h"
void Debug::DrawBoxDebug(Tmpl8::Surface* screen, Camera* camera, float2 pos, int2 size, uint color)
{
	int2 topLeft = camera->WorldToScreen(pos);
	int2 bottomRight = camera->WorldToScreen({ pos.x + size.x, pos.y + size.y });
	
		// Top and bottom edges
		for (int x = topLeft.x; x <= bottomRight.x; x++)
		{
			screen->Plot(x, topLeft.y, color);
			screen->Plot(x, bottomRight.y, color);
		}
	
		// Left and right edges
		for (int y = topLeft.y; y <= bottomRight.y; y++)
		{
			screen->Plot(topLeft.x, y, color);
			screen->Plot(bottomRight.x, y, color);
		}
}

