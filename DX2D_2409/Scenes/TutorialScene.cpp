#include "Framework.h"
#include "TutorialScene.h"

TutorialScene::TutorialScene()
{
    rects.reserve(POOL_SIZE);
    //rects.resize(POOL_SIZE);// Rect* rects = new Rect[100];
    //
    //for (Rect* rect : rects)
    //{
    //
    //}

    for (int i = 0; i < 1; i++)
    {
        rects.push_back(new Rect());
        rects.back()->SetColor(1, 0, 0);
        //'rects.back()->SetActive(false);
    }
}

TutorialScene::~TutorialScene()
{
}

void TutorialScene::Update()
{
    //count++;
    //
    //if (count > SPAWN_INTERVAL)
    //{
    //    count = 0;
    //
    //    Spawn();
    //}

    if (GetAsyncKeyState('W'))
    {
        rects[0]->Translate(0, 0.1f);
    }

    rects[0]->UpdateWorld();
}

void TutorialScene::Render()
{
    for (Rect* rect : rects)
        rect->Render();
}

void TutorialScene::Spawn()
{
    Rect* rect = rects[spawnNum++];
    rect->SetPos(GameMath::Random(0, SCREEN_WIDTH), GameMath::Random(0, SCREEN_HEIGHT));
    float r = GameMath::Random(0.0f, 1.0f);
    float g = GameMath::Random(0.0f, 1.0f);
    float b = GameMath::Random(0.0f, 1.0f);
    rect->SetColor(r, g, b);
    rect->SetActive(true);

    rect->UpdateWorld();
    //rects.push_back(rect);

    
}

void TutorialScene::PostRender()
{
}
