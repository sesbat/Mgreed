#pragma once
#include "Framework.h"

class SokobanPlayer : public BoxCollider
{
public:
	SokobanPlayer();
	~SokobanPlayer();

	void Update();
	void Render();

	void Move();
private:
	Quad* player;

	float speed = 500.0f;
};