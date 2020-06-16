#pragma once

#include "walking_dino.h"

Walking_Dino::Walking_Dino(std::string id)
	: Game_Object(id, "Texture.Dino.Walking")
{
	// _x = 150;
	// _y = 50;
	_translation = Vector_2D(150, 50);
	_velocity = Vector_2D(0.02f, 0);
}
Walking_Dino::~Walking_Dino()
{
}

void Walking_Dino::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Walking_Dino::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}