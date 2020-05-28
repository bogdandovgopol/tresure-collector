#pragma once

#include "Coin.h"

Coin::Coin(std::string id)
	: Game_Object(id, "Texture.Coin")
{
	_height = 30;
	_width = 30;
	//_translation = Vector_2D(150, 50);
	//_velocity = Vector_2D(0.02f, 0);
}
Coin::~Coin()
{
}

void Coin::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Coin::simulate_AI(Uint32, Assets*, Input*, Scene*)
{
}