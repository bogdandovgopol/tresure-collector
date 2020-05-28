#pragma once

#include "Coin.h"
#include "player.h"
#include "Sound.h"
#include <iostream>

Coin::Coin(std::string id) : Game_Object(id, "Texture.Coin")
{
	_id = id;
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

void Coin::simulate_AI(Uint32, Assets* assets, Input*, Scene* scene)
{

	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D portal_center = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (portal_center - player_center).magnitude();

	if (distance_to_player < 20.0f)
	{
		player->collect_coin(1);
		const int coin_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Coin");
		Mix_PlayChannel(coin_channel, sound->data(), 0);
		scene->remove_game_object(_id);
		//Mix_HaltChannel(coin_channel);
		//std::cout << "SOUND" << std::endl;

	}
}