#pragma once

#include "player.h"
#include "Sound.h"

Player::Player(std::string id)
	: Game_Object(id, "Texture.Player.Idle")
{
	_height = 80;
	_width = 80;
	_speed = 0.1f;

	_state.push(State::Idle);
}
Player::~Player()
{
}

void Player::render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config)
{
	
	Animated_Texture* texture = (Animated_Texture*)assets->get_asset(_texture_id);
	texture->update_frame(milliseconds_to_simulate);

	//dont let player go outside of the frame
	if (_translation.x() > 630) {
		_translation = Vector_2D(630, _translation.y());
	}
	else if (_translation.x() < 0) {
		_translation = Vector_2D(0, _translation.y());
	}
	else if (_translation.y() > 595) {
		_translation = Vector_2D(_translation.x(), 595);
	}
	else if (_translation.y() < 0) {
		_translation = Vector_2D(_translation.x(), 0);
	}

	Game_Object::render(milliseconds_to_simulate, assets, renderer, config);
}

void Player::simulate_AI(Uint32, Assets* assets, Input* input, Scene* )
{

	//play die animation when X key is pressed
	if (input->is_button_state(Input::Button::DIE, Input::Button_State::PRESSED))
	{
		push_state(State::Die, assets);
	}

	switch (_state.top())
	{
	case State::Idle:
		if (_velocity.magnitude() > 0.0f)
		{
			push_state(State::Walk, assets);
		}
		break;
	case State::Walk:
		if (_velocity.magnitude() == 0.0f)
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

void Player::collect_coin(int worth)
{
	_score += worth;
}

int Player::get_score()
{
	return _score;
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
	case State::Die:
	{
		const int die_channel = 2;
		Mix_HaltChannel(die_channel);
		break;
	}
	}
}
