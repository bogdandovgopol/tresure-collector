#include "game_scene.h"
#include "Coin.h"
#include "player.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	Game_Object* coin = new Coin("Texture.Coin");
	_game_objects[coin->id()] = coin;

	Game_Object* player = new Player("Player");
	_game_objects[player->id()] = player;
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{
}