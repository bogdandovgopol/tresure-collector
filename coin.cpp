#pragma once

#include "Coin.h"
#include "player.h"
#include "Sound.h"
#include <iostream>
#include <time.h>

Coin::Coin(std::string id) : Game_Object(id, "Texture.Coin")
{
	_id = id;
	_height = 30;
	_width = 30;
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

void Coin::simulate_AI(Uint32, Assets* assets, Input*, Scene* scene, Configuration*)
{

	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D coin_center = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (coin_center - player_center).magnitude();

	//coin-player collison trigger check
	if (distance_to_player < 30.0f)
	{
		player->collect_coin(1);
		const int coin_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Coin");
		Mix_PlayChannel(coin_channel, sound->data(), 0);
		scene->remove_game_object(_id);

	}
}