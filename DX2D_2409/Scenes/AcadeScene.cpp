#include "Framework.h"
#include "AcadeScene.h"

AcadeScene::AcadeScene()
{
    land = new ImageObject(L"Textures/Acade/land.png");
    land->SetPos(CENTER_X, 100);
    land->Update();

    mario = new Mario();
    mario->SetLandCollider(land);

    BrickManager::Get();
}

AcadeScene::~AcadeScene()
{
    delete land;
    delete mario;

    BrickManager::Delete();
}

void AcadeScene::Update()
{
    mario->Update();
}

void AcadeScene::Render()
{
    land->Render();
    mario->Render();

    BrickManager::Get()->Render();
}

void AcadeScene::PostRender()
{
}
