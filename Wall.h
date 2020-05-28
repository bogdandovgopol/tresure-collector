#pragma once

#include "game_object.h"

class Wall : public Game_Object
{
public:
	Wall(std::string id);
	~Wall();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene) override;
	void setSize(int width, int height);
};