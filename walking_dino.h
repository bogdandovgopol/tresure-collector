#pragma once

#include "game_object.h"

class Walking_Dino : public Game_Object
{
public:
	Walking_Dino(std::string id);
	~Walking_Dino();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;
};