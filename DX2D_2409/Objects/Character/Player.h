#pragma once
#include "Framework.h"

class Player : public Character
{
private:
	enum ActionState
	{
		IDLE, MOVE, JUMP, DEAD
	};
public:
	Player();
	~Player();

	void Update();
	void Render();

	void OnGround();

private:
	void Move();
	void Jump();
	void Attack();
	void SetActionState(ActionState state);
	void CreateActions();
private:
	ActionState curState = IDLE;
	map<ActionState, Action*> actions;

	Inventory* inventory;
	Slider* hpBar;
};
