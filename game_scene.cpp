#include "game_scene.h"
#include "Coin.h"
#include "Bomb.h"
#include "player.h"
#include "Wall.h"
#include "Portal_Entry.h"
#include "Portal_Exit.h"
#include "text.h"

Game_Scene::Game_Scene()
	: Scene("Game")
{

	Bomb* bomb = new Bomb("Texture.Bomb");
	add_game_object(bomb);

	Player* player = new Player("Player");
	player->set_translation(Vector_2D(320, 600));
	add_game_object(player);

	load_coins();

	//Wall left
	{
		Wall* wall = new Wall("Texture.Wall.Left");
		wall->setSize(10, 700);
		wall->set_translation(Vector_2D(0, 0));
		add_game_object(wall);
	}

	//Wall right
	{
		Wall* wall = new Wall("Texture.Wall.Right");
		wall->setSize(10, 700);
		wall->set_translation(Vector_2D(690, 0));
		add_game_object(wall);
	}

	//Wall top
	{
		Wall* wall = new Wall("Texture.Wall.Top");
		wall->setSize(700, 10);
		wall->set_translation(Vector_2D(0, 0));
		add_game_object(wall);
	}

	//Wall bottom
	{
		Wall* wall = new Wall("Texture.Wall.Bottom");
		wall->setSize(700, 10);
		wall->set_translation(Vector_2D(0, 670));
		add_game_object(wall);
	}
	

	
}

Game_Scene::~Game_Scene()
{
}

void Game_Scene::update(SDL_Window*)
{
}

void Game_Scene::load_coins()
{
	{
		Coin* coin = new Coin("Texture.Coin1");
		coin->set_translation(Vector_2D(320, 100));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin2");
		coin->set_translation(Vector_2D(500, 180));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin3");
		coin->set_translation(Vector_2D(70, 210));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin4");
		coin->set_translation(Vector_2D(130, 310));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin5");
		coin->set_translation(Vector_2D(300, 310));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin6");
		coin->set_translation(Vector_2D(400, 410));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin7");
		coin->set_translation(Vector_2D(220, 130));
		add_game_object(coin);;
	}

	{
		Coin* coin = new Coin("Texture.Coin8");
		coin->set_translation(Vector_2D(420, 530));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin9");
		coin->set_translation(Vector_2D(530, 430));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin10");
		coin->set_translation(Vector_2D(570, 300));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin11");
		coin->set_translation(Vector_2D(580, 580));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin12");
		coin->set_translation(Vector_2D(60, 580));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin13");
		coin->set_translation(Vector_2D(210, 380));
		add_game_object(coin);
	}

	{
		Coin* coin = new Coin("Texture.Coin14");
		coin->set_translation(Vector_2D(280, 490));
		add_game_object(coin);
	}
}
