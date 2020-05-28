#pragma once
#include <string>

struct Configuration
{
	bool should_display_ids = false;
	bool should_display_position = false;
	bool should_display_colliders = true;

	int window_width  = 700;
	int window_height = 700;
};