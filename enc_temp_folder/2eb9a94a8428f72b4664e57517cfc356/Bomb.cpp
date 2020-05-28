#pragma once

#include "Bomb.h"

Bomb::Bomb(std::string id)
	: Game_Object(id, "Texture.Bomb")
{
	_height = 40;
	_width = 40;
	_translation = Vector_2D(330, 300);
	_velocity = Vector_2D(0.04f, 0);
}
Bomb::~Bomb()
{
}

void Bomb::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Bomb::simulate_AI(Uint32, Assets*, Input*, Scene* scene)
{
	if (_translation.x() > 400.f && !_has_spawned_another) {
		Bomb* bomb = new Bomb(id() + "new");
		scene->add_game_object(bomb);
		_has_spawned_another = true;
	}
	else if (_translation.x() > 700.f) {
		scene->remove_game_object(id());
	}
}