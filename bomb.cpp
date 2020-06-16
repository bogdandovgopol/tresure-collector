#pragma once

#include "Bomb.h"
#include "player.h"
#include "Sound.h"

#include <stdio.h>
#include <stdlib.h>
#include <time.h>
#include <iostream>

Bomb::Bomb(std::string id)
	: Game_Object(id, "Texture.Bomb")
{
	_height = 40;
	_width = 40;
	_translation = Vector_2D(330, 300);
	float speed = 4.f;
	int random_number;

	srand((unsigned int)time(NULL));
	random_number = rand() % 8 + 1;
	std::cout << random_number << std::endl;

	//change bomb direction based on a random number
	switch (random_number) {
	case 1:
		_velocity = Vector_2D(0.04f * speed, 0.00f * speed);
		break;
	case 2:
		_velocity = Vector_2D(0.02f * speed, 0.02f * speed);
		break;
	case 3:
		_velocity = Vector_2D(0.00f * speed, 0.04f * speed);
		break;
	case 4:
		_velocity = Vector_2D(-0.02f * speed, 0.02f * speed);
		break;
	case 5:
		_velocity = Vector_2D(-0.04f * speed, 0.00f * speed);
		break;
	case 6:
		_velocity = Vector_2D(-0.02f * speed, -0.02f * speed);
		break;
	case 7:
		_velocity = Vector_2D(0.00f * speed, -0.04f * speed);
		break;
	case 8:
		_velocity = Vector_2D(0.02f * speed, -0.02f * speed);
		break;
	}
	
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

void Bomb::simulate_AI(Uint32, Assets* assets, Input*, Scene* scene, Configuration* config)
{
	//spam a new bomb if player alive
	if (config->player_lose == false) {
		if (((_translation.x() > 400.f || _translation.y() > 400.f) || (_translation.x() < 200.f || _translation.y() < 200.f)) && !_has_spawned_another) {
			{
				Bomb* bomb = new Bomb(id() + "new");
				scene->add_game_object(bomb);
				_has_spawned_another = true;
			}
		}
		else if (_translation.x() > 700.f || _translation.y() > 700.f) {
			scene->remove_game_object(id());
		}
	}

	//track bomb-player collision trigger
	Player* player = (Player*)scene->get_game_object("Player");

	Vector_2D bomb_center = _translation + Vector_2D((float)_width / 2, (float)_height / 2);
	Vector_2D player_center = player->translation() + Vector_2D((float)player->width() / 2, (float)player->height() / 2);

	float distance_to_player = (bomb_center - player_center).magnitude();

	//player got hit by a bomb
	if (distance_to_player < 30.0f)
	{
	
		//play explosion sound
		{
			const int explosion_channel = 2;
			Sound* sound = (Sound*)assets->get_asset("Sound.Explosion");
			Mix_PlayChannel(explosion_channel, sound->data(), 0);
		}
		scene->remove_game_object(_id);
		player->die(config);

	}
}