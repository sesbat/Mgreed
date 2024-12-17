#pragma once
#include "Framework.h"

class Player : public Character
{
private:
	const int MAX_DASH_COUNT = 2;
	const float DASH_COOL_DOWN = 1.0f;
public:
	enum ActionState
	{
		IDLE, RUN, JUMP, DASH
	};
public:
	Player();
	~Player();

	void Update();
	void Render();

	void Land();
	bool IsGround() { return isGround; };

	void CheckCollisionTiles(const vector<vector<Tile*>>& tiles);
	void SetActionState(ActionState state);
private:
	void Move();
	void Jump();
	void Attack();
	void Dash();
	void SetDirection();

	void CursorFollow();

	void CreateActions();
private:
	ActionState curState = IDLE;
	map<ActionState, Action*> actions;

	Inventory* inventory;
	Slider* hpBar;

	int dashCount = 0;
	float coolDownTimer = 0.0f;
	bool isGround = false;

	Weapon* currentWeapon = nullptr;
	BoxCollider* handle = nullptr;
	float handleRadius = 20.0f;
};
