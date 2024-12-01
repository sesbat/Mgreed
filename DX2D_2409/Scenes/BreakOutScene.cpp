#include "Framework.h"
#include "BreakOutScene.h"

BreakOutScene::BreakOutScene()
{
    background = new ImageObject(L"Textures/Breakout/Background.png");
    Vector2 size = background->OriginSize();
    size.x -= 30.0f;
    size.y -= 30.0f;
    background->UpdateSize(size);
    background->SetPos(CENTER);
    background->SetScale(1.5f, 1.5f);
    background->Update();

    controlBar = new ControlBar();
    controlBar->SetBrackground(background);

    ball = new Ball();
    ball->SetControlBar(controlBar);
    ball->SetBackground(background);

    //BlockManager::Get()->LoadStage("DataTables/Stage2.csv", background->LeftTop());
    BlockManager::Get()->SetStartPos(background->LeftTop());
    BlockManager::Get()->LoadStage(0);
}

BreakOutScene::~BreakOutScene()
{
    delete background;
    delete controlBar;
    delete ball;

    BlockManager::Delete();
}

void BreakOutScene::Update()
{
    controlBar->Update();
    ball->Update();
}

void BreakOutScene::Render()
{
    background->Render();
    controlBar->Render();
    ball->Render();

    BlockManager::Get()->Render();
}

void BreakOutScene::PostRender()
{
}
