#pragma once

#include "player.h"
#include "Sound.h"

Player::Player(std::string id)
	: Game_Object(id, "Texture.Player.Idle")
{
	_speed = 0.1f;

	_collider.set_radius(_width / 5.0f);
	_collider.set_translation(Vector_2D(_width / 2.0f, (float)_height));

	_state.push(State::Idle);
}
Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Player::simulate_AI(Uint32, Assets* assets, Input* input, Scene* )
{
	//play attack animation when SPACEBAR is pressed
	if (input->is_button_state(Input::Button::ATTACK, Input::Button_State::PRESSED))
	{
		push_state(State::Attack, assets);
	}

	//play die animation when X key is pressed
	if (input->is_button_state(Input::Button::DIE, Input::Button_State::PRESSED))
	{
		push_state(State::Die, assets);
	}

	switch (_state.top())
	{
	case State::Idle:
		if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::DOWN) && _velocity.magnitude() > 0.0f)
		{
			push_state(State::Run, assets);
		}
		else if (_velocity.magnitude() > 0.0f)
		{
			push_state(State::Walk, assets);
		}
		break;
	case State::Walk:
		if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::PRESSED))
		{
			push_state(State::Run, assets);
		}
		break;
	case State::Run:
		if (_velocity.magnitude() == 0.0f)
		{
			pop_state(assets);
		}
		else if (input->is_button_state(Input::Button::RUNNING, Input::Button_State::RELEASED))
		{
			pop_state(assets);
		}
		break;
	}

	_velocity = Vector_2D(0, 0);

	if(input->is_button_state(Input::Button::RIGHT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(1.0f, 0);
	}

	if(input->is_button_state(Input::Button::LEFT, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(-1.0f, 0);
	}

	if(input->is_button_state(Input::Button::UP, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, -1.0f);
	}

	if(input->is_button_state(Input::Button::DOWN, Input::Button_State::DOWN))
	{
		_velocity += Vector_2D(0, 1.0f);
	}

	_velocity.normalize();
	_velocity.scale(_speed);
}

void Player::set_speed(float speed)
{
	_speed = speed;
}
float Player::speed()
{
	return _speed;
}

void Player::set_texture(std::string texture_id)
{
	_texture_id = texture_id;
}

void Player::push_state(State state, Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.push(state);
	handle_enter_state(_state.top(), assets);
}
void Player::pop_state(Assets* assets)
{
	handle_exit_state(_state.top(), assets);

	_state.pop();
	handle_enter_state(_state.top(), assets);
}

void Player::handle_enter_state(State state, Assets* assets)
{
	switch (state)
	{
	case State::Idle:
		_texture_id = "Texture.Player.Idle";
		break;

	case State::Walk:
	{
		_texture_id = "Texture.Player.Walk";
		_speed = 0.15f;

		const int walking_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Walking");
		Mix_PlayChannel(walking_channel, sound->data(), -1);

		break;
	}
	case State::Run:
	{
		_texture_id = "Texture.Player.Run";
		_speed = 0.3f;

		const int running_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Running");
		Mix_PlayChannel(running_channel, sound->data(), -1);

		break;
	}
	case State::Attack:
	{
		_texture_id = "Texture.Player.Attack";
		const int attack_channel = 1;
		Sound* sound = (Sound*)assets->get_asset("Sound.Attack");
		Mix_PlayChannel(attack_channel, sound->data(), -1);
		break;
	}
	case State::Die:
	{
		_texture_id = "Texture.Player.Die";
		_speed = 0.0f;
		const int die_channel = 2;
		Sound* sound = (Sound*)assets->get_asset("Sound.Die");
		Mix_PlayChannel(die_channel, sound->data(), -1);
		break;
	}
	}
}

void Player::handle_exit_state(State state, Assets*)
{
	switch (state)
	{
	case State::Idle:
		break;
	case State::Walk:
	{
		const int walking_channel = 1;
		Mix_HaltChannel(walking_channel);
		break;
	}
	case State::Run:
	{
		const int running_channel = 2;
		Mix_HaltChannel(running_channel);
		break;
	}
	case State::Attack:
	{
		const int attack_channel = 1;
		Mix_HaltChannel(attack_channel);
		break;
	}
	case State::Die:
	{
		const int die_channel = 2;
		Mix_HaltChannel(die_channel);
		break;
	}
	}
}
