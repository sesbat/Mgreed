#pragma once

class PlayerDash : public PlayerMove
{
private:
	const float DASH_POWER = 1000.0f;

	enum DashState
	{
		LOOP , END
	};
public:
	PlayerDash(Player* player);

	void Update();
	void Start();
	void Loop();
private:
	
};
