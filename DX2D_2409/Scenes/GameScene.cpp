#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	//curMap = MapManager::Get()->GetSelectedMap();
	CAM->SetTarget(PLAYER);

	goldbar = new GoldBar();
	goldbar->SetPos(CENTER);
	aed = new AED();
	aed->SetPos(CENTER);
	coin = new Coin();
	coin->SetPos(CENTER);
}

GameScene::~GameScene()
{
	delete curMap;
}

void GameScene::Start()
{
	curMap = MapManager::Get()->GetSelectedMap();
}

void GameScene::Update()
{
	curMap->Update();
	PLAYER->Update();
	goldbar->Update();
	aed->Update();
	coin->Update();
}

void GameScene::Render()
{
	curMap->Render();
	PLAYER->Render();
	goldbar->Render();
	aed->Render();
	coin->Render();
}

void GameScene::PostRender()
{

}

void GameScene::LoadGameMap(const string& fileName)
{
	MapManager::Get()->LoadAllMaps(fileName);
	curMap = MapManager::Get()->GetSelectedMap();
}
