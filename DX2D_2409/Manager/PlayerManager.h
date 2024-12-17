#pragma once

class PlayerManager : public Singleton<PlayerManager>
{
private:
	friend class Singleton;

	PlayerManager();
	~PlayerManager();

	void Update();
	void Render();

public:
	Player* GetPlayer() { return player; }

private:
	Player* player;
};