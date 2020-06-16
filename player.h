#pragma once

#include "game_object.h"
#include <stack>

class Player : public Game_Object
{
public:
	Player(std::string id);
	~Player();

	virtual void simulate_AI(Uint32 milliseconds_to_simulate, Assets* assets, Input* input, Scene* scene, Configuration* config) override;
	virtual void render(Uint32 milliseconds_to_simulate, Assets* assets, SDL_Renderer* renderer, Configuration* config) override;

	void set_speed(float speed);
	float speed();

	void set_texture(std::string texture_id);

	enum class State 
	{
		Idle,
		Walk,
		Die,
		Win
	};
	void push_state(State state, Assets* assets);
	void pop_state(Assets* assets);

	void collect_coin(int worth);
	int get_score();
	void win(Configuration* config);
	void die(Configuration* config);
	SDL_Renderer* get_renderer();

private:
	void handle_enter_state(State state, Assets* assets);
	void handle_exit_state(State state, Assets* assets);

	int _score = 0;
	float _speed;
	SDL_Renderer* _renderer;
	std::stack<State> _state;
};