#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    EffectManager::Get()->Add("Fire", 20, L"Textures/Effect/fire_8x2.png", { 8, 2 }, 1.0f, true);
    
    BulletManager::Get();

    robot = new Robot();
    boss = new Boss(robot);
    robot->SetBoss(boss);
}

AnimationScene::~AnimationScene()
{
    delete robot;
    delete boss;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    /*if (KEY->Down(VK_LBUTTON))
    {
        EffectManager::Get()->Play("Fire", mousePos);
    }*/
    if (KEY->Down('R'))
    {
        EffectManager::Get()->Play("Laser", { boss->GetPos().x,boss->GetPos().y - 100 });
    }

    robot->Update();
    boss->Update();

    BulletManager::Get()->Update();
}

void AnimationScene::Render()
{
    robot->Render();
    boss->Render();

    BulletManager::Get()->Render();
}

void AnimationScene::PostRender()
{
    robot->Edit();
    boss->Edit();
}
