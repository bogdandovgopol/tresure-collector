#include "assets.h"
#include "texture.h"
#include "animated_texture.h"
#include "Sound.h"
#include "text.h"

#include <iostream>

Assets::Assets(SDL_Renderer* renderer)
{
	// Collider Texture.
	{
		Texture* texture = new Texture("Texture.Collider", "Assets/collider.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Cache BG Texture.
	{
		Texture* texture = new Texture("Texture.BG", "Assets/bg.png", renderer);
		_assets[texture->id()] = texture;
	}

	// Coin texture.
	{
		const int frame_count = 9;
		const Uint32 frame_duration_milliseconds = 1000;
		Asset* coin_texture = new Animated_Texture("Texture.Coin", "Assets/coin.png", renderer, frame_count, frame_duration_milliseconds, true);
		_assets[coin_texture->id()] = coin_texture;
	}

	// Bomb texture.
	{
		const int frame_count = 1;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* coin_texture = new Animated_Texture("Texture.Bomb", "Assets/bomb.png", renderer, frame_count, frame_duration_milliseconds, false);
		_assets[coin_texture->id()] = coin_texture;
	}

	// Create player idle texture.
	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("Texture.Player.Idle", "Assets/player.idle.png", renderer, frame_count, frame_duration_milliseconds, true);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	// Create player walking texture.
	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("Texture.Player.Walk","Assets/player.walk.png", renderer, frame_count, frame_duration_milliseconds, true);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	// Create player die texture.
	{
		const int frame_count = 7;
		const Uint32 frame_duration_milliseconds = 100;
		Asset* player_animated_texture = new Animated_Texture("Texture.Player.Die", "Assets/player.die.png", renderer, frame_count, frame_duration_milliseconds, false);
		_assets[player_animated_texture->id()] = player_animated_texture;
	}

	// Create music sound
	{
		Sound* sound = new Sound("Sound.Music", "Assets/music.wav");
		_assets[sound->id()] = sound;

		Mix_PlayChannel(0, sound->data(), -1);
	}

	// Create coin pickup sound
	{
		Sound* sound = new Sound("Sound.Coin", "Assets/coin.wav");
		_assets[sound->id()] = sound;
	}

	// Create explosion sound
	{
		Sound* sound = new Sound("Sound.Explosion", "Assets/explosion.wav");
		_assets[sound->id()] = sound;
	}

	// Create walking sound
	{
		Sound* sound = new Sound("Sound.Walking", "Assets/walking.wav");
		_assets[sound->id()] = sound;
	}

	// Create die sound
	{
		Sound* sound = new Sound("Sound.Die", "Assets/die.wav");
		_assets[sound->id()] = sound;
	}
}

Assets::~Assets()
{

}

Asset* Assets::get_asset(std::string id)
{
	if(_assets.find(id) == _assets.end())
	{
		std::cout << "Attempted to find an asset that was not loaded. ID: " << id << std::endl;
		exit(1);
	}

	return _assets[id];
}