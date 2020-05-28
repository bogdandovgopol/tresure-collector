#include "game_scene.h"
#include "dino.h"
#include "walking_dino.h"
#include "player.h"
#include "Portal_Entry.h"
#include "Portal_Exit.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	Game_Object* dino = new Dino("Dino");
	_game_objects[dino->id()] = dino;

	Game_Object* dino_walking = new Walking_Dino("Dino.Walking");
	_game_objects[dino_walking->id()] = dino_walking;

	Game_Object* player = new Player("Player");
	_game_objects[player->id()] = player;

	Game_Object* portal_entry = new Portal_Entry();
	_game_objects[portal_entry->id()] = portal_entry;

	Game_Object* portal_exit = new Portal_Exit();
	_game_objects[portal_exit->id()] = portal_exit;
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{
}