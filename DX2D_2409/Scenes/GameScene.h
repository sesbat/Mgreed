#pragma once

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Update() override;
	void Render() override;
	void PostRender() override;

private:
	Player* player;
	Room* room;
};
