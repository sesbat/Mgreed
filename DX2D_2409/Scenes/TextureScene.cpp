#include "Framework.h"
#include "TextureScene.h"

TextureScene::TextureScene()
{
    //rect = new Quad(Vector2(300, 300));
    rect = new Quad(L"Textures/airplane.png");
    rect->SetPos(CENTER);
    rect->UpdateWorld();
}

TextureScene::~TextureScene()
{
    delete rect;
}

void TextureScene::Update()
{
}

void TextureScene::Render()
{
    rect->Render();
}

void TextureScene::PostRender()
{
}
