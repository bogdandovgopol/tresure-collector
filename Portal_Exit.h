#pragma once

#include "game_object.h"

class Portal_Exit : public Game_Object
{
public:
	Portal_Exit();
	~Portal_Exit();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Configuration* config) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;
};
