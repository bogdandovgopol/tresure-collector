#pragma once

#include <map>

class Input
{
public:
	Input();
	~Input();

	enum class Button
	{
		QUIT,

		UP,
		DOWN,
		LEFT,
		RIGHT,

		DIE,

		INCREASE_SPEED,
		DECREASE_SPEED,
		CHANGE_TO_DINO,

		SHOW_CREDITS,
		SHOW_LIBRARIES,
		SHOW_VERSION,

		DEBUG_SHOW_IDS,
		DEBUG_SHOW_POSITION,

		FULL_SCREEN,
		REVERSE_FULL_SCREEN
	};

	enum class Button_State
	{
		PRESSED,
		DOWN,
		RELEASED,
		UP
	};

	void get_input();
	bool is_button_state(Button type, Button_State state);

private:
	std::map<Button, Button_State> _button_state;
};