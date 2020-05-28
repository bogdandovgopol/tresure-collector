#include "game_scene.h"
#include "Coin.h"
#include "player.h"
#include "Wall.h"
#include "Portal_Entry.h"
#include "Portal_Exit.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{
	Coin* coin = new Coin("Texture.Coin");
	_game_objects[coin->id()] = coin;


	Player* player = new Player("Player");
	_game_objects[player->id()] = player;

	//Wall left
	{
		Wall* wall = new Wall("Texture.Wall.Left");
		wall->setSize(10, 700);
		wall->set_translation(Vector_2D(0, 0));
		_game_objects[wall->id()] = wall;
	}

	//Wall right
	{
		Wall* wall = new Wall("Texture.Wall.Right");
		wall->setSize(10, 700);
		wall->set_translation(Vector_2D(690, 0));
		_game_objects[wall->id()] = wall;
	}

	//Wall top
	{
		Wall* wall = new Wall("Texture.Wall.Top");
		wall->setSize(700, 10);
		wall->set_translation(Vector_2D(0, 0));
		_game_objects[wall->id()] = wall;
	}

	//Wall bottom
	{
		Wall* wall = new Wall("Texture.Wall.Bottom");
		wall->setSize(700, 10);
		wall->set_translation(Vector_2D(0, 670));
		_game_objects[wall->id()] = wall;
	}
	

	
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{
}