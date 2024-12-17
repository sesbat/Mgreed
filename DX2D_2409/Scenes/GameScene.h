#pragma once

class GameScene : public Scene
{
public:
	GameScene();
	~GameScene();

	void Start() override;

	void Update() override;
	void Render() override;
	void PostRender() override;

	void LoadGameMap(const string& fileName);
private:
	Map* curMap;
	GoldBar* goldbar;
	AED* aed;
	Coin* coin;
};
