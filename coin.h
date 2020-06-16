#pragma once

#include "game_object.h"

class Coin : public Game_Object
{
public:
	Coin(std::string id);
	~Coin();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Configuration* config) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;

private:
	std::string _id;
};