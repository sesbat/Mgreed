#pragma once

class PlayerMove : public PlayerAction
{
public:
	PlayerMove(Player* player);

	void Update() override;
};