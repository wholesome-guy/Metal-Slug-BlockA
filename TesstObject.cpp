#include "precomp.h"
#include "TesstObject.h"
#include "Camera.h"
#include <iostream>
TesstObject::TesstObject()
{
	_sprite = new Sprite(new Surface("assets/block.png"), 1);
	_height = _sprite->GetHeight();
	_width = _sprite->GetWidth();

	int count = _width * _height;
	_originalPixels = new uint[count];
	memcpy(_originalPixels, _sprite->GetBuffer(), count * sizeof(uint));
}

void TesstObject::Collision(bool collision)
{
	uint* pixels = _sprite->GetBuffer();
	int count = _width * _height;

	if (collision)
	{
		for (int i = 0; i < count; i++) pixels[i] = 0xffffff;
	}
	else
	{
		memcpy(pixels, _originalPixels, count * sizeof(uint));

	}
}


void TesstObject::Render(Tmpl8::Surface* screen, Camera* camera)
{
	int2 position = camera->WorldToScreen(_position);


	_sprite->Draw(screen, position.x, position.y, false);
}


