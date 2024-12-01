#include "Framework.h"
#include "ShootingScene.h"

ShootingScene::ShootingScene()
{
    player = new Player();
    //CAM->SetTarget(player);
}

ShootingScene::~ShootingScene()
{
    delete player;

    BulletManager::Delete();
}

void ShootingScene::Update()
{
    time++;
    if (time > INTERVAL)
    {
        time = 0;
        RandomFire();
    }    

    BulletManager::Get()->Collision(player, "Enemy");

    player->Update();
    BulletManager::Get()->Update();
}

void ShootingScene::Render()
{
    player->Render();
    BulletManager::Get()->Render();
}

void ShootingScene::RandomFire()
{
    GameMath::Direction dir = (GameMath::Direction)GameMath::Random(0, 4);
    Vector2 pos;

    switch (dir)
    {
    case GameMath::Direction::UP:
        pos.x = GameMath::Random(0, SCREEN_WIDTH);
        pos.y = SCREEN_HEIGHT;
        break;
    case GameMath::Direction::DOWN:
        pos.x = GameMath::Random(0, SCREEN_WIDTH);
        pos.y = 0;
        break;
    case GameMath::Direction::LEFT:
        pos.x = 0;
        pos.y = GameMath::Random(0, SCREEN_HEIGHT);
        break;
    case GameMath::Direction::RIGHT:
        pos.x = SCREEN_WIDTH;
        pos.y = GameMath::Random(0, SCREEN_HEIGHT);
        break;    
    }

    BulletManager::Get()->Fire(pos, player->GetPos() - pos, "Enemy");
}

void ShootingScene::PostRender()
{
    player->PostRender();
}
