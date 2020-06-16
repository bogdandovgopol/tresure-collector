#pragma once

#include "Wall.h"

Wall::Wall(std::string id)
	: Game_Object(id, "Texture.BG")
{
	// _x = 50;
	// _y = 50;
	_translation = Vector_2D(50, 50);
}
Wall::~Wall()
{
}
void Wall::simulate_AI(Uint32, Assets*, Input*, Scene*, Configuration*)
{
}

void Wall::setSize(int width, int height)
{
	_width = width;
	_height = height;
}
