#pragma once

class PlayerAction : public Action
{
public:
	PlayerAction(Player* player);

protected:
	Player* player;
};