#pragma once

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Update() override;
	void Render() override;
	void PostRender() override;

	void LoadGameMap(const string& fileName);
private:
	Player* player;
	Map* curMap;
};
