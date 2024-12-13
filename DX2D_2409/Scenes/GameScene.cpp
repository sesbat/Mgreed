#include "Framework.h"
#include "GameScene.h"

GameScene::GameScene()
{
	player = new Player();
	room = nullptr;
}

GameScene::~GameScene()
{
	delete room;
	delete player;
}

void GameScene::Update()
{
	room->Update();
	player->Update();
}

void GameScene::Render()
{
	room->Render();
	player->Render();
}

void GameScene::PostRender()
{

}
