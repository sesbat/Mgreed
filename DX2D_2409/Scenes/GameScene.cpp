#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	player = new Player();
	LoadGameMap("map_data.bin");
}

GameScene::~GameScene()
{
	delete player;
	delete curMap;
}

void GameScene::Update()
{
	curMap->Update();
	player->Update();
}

void GameScene::Render()
{
	curMap->Render();
	player->Render();
}

void GameScene::PostRender()
{

}

void GameScene::LoadGameMap(const string& fileName)
{
	MapManager::Get()->LoadAllMaps(fileName);
	curMap = MapManager::Get()->GetSelectedMap();
}
