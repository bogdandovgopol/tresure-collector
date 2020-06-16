#pragma once
#include <string>

struct Configuration
{
	bool should_display_ids = false;
	bool should_display_position = false;
	bool should_display_colliders = false;
	
	bool player_win = false;
	bool player_lose = false;

	int window_width  = 700;
	int window_height = 700;
};