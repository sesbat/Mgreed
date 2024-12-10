#include "Framework.h"
#include "MapEditorScene.h"

MapEditorScene::MapEditorScene()
{
	mapEditor = new MapEditor();
}

MapEditorScene::~MapEditorScene()
{
	delete mapEditor;
}

void MapEditorScene::Update()
{
	mapEditor->Update();
}

void MapEditorScene::Render()
{
	mapEditor->Render();
}

void MapEditorScene::PostRender()
{
	mapEditor->Edit();
}
