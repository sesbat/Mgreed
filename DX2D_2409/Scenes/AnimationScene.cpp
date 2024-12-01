#include "Framework.h"
#include "AnimationScene.h"

AnimationScene::AnimationScene()
{
    EffectManager::Get()->Add("Fire", 20, L"Textures/Effect/fire_8x2.png", { 8, 2 }, 1.0f, true);

    BulletManager::Get();

    robot = new Robot();
}

AnimationScene::~AnimationScene()
{
    delete robot;

    BulletManager::Delete();
}

void AnimationScene::Update()
{
    if (KEY->Down(VK_LBUTTON))
    {
        EffectManager::Get()->Play("Fire", mousePos);
    }

    robot->Update();

    BulletManager::Get()->Update();
}

void AnimationScene::Render()
{
    robot->Render();

    BulletManager::Get()->Render();
}

void AnimationScene::PostRender()
{
    robot->Edit();
}
