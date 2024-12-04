#include "Framework.h"
#include "TileMapScene.h"

TileMapScene::TileMapScene()
{
    mapEditor = new MapEditor();
}

TileMapScene::~TileMapScene()
{
    delete mapEditor;
}

void TileMapScene::PreRender()
{
    mapEditor->PreRender();
}

void TileMapScene::Update()
{
    mapEditor->Update();
}

void TileMapScene::Render()
{
    mapEditor->Render();
}

void TileMapScene::PostRender()
{
    mapEditor->Edit();
}
