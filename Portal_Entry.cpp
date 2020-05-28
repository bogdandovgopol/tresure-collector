#pragma once

#include "portal_entry.h"
#include "scene.h"
#include "player.h"

Portal_Entry::Portal_Entry()
	: Game_Object("Portal.Entry", "Texture.Portal.Entry")
{
	_width = 200;
	_height = 200;
	_translation = Vector_2D(50, 300);
}

Portal_Entry::~Portal_Entry()
{

}
void Portal_Entry::simulate_AI(Uint32 , Assets* , Input*, Scene* scene)
{
	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D portal_center = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	if (distance_to_player < 50.0f)
	{
		player->set_translation(Vector_2D(300, 600));
	}
}
void Portal_Entry::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}
