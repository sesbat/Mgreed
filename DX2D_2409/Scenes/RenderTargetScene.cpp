#include "Framework.h"
#include "RenderTargetScene.h"

RenderTargetScene::RenderTargetScene()
{
    bg = new Quad(L"Textures/BreakOut/Background.png");
    bg->SetPos(CENTER);
    bg->UpdateWorld();
    robot = new Robot();

    renderTarget = new RenderTarget();
    
    Texture* targetTexture = Texture::Add(L"Target", renderTarget->GetSRV());

    for (int i = 0; i < 4; i++)
    {
        Vector2 offset = CENTER / 2;
        Vector2 temp;
        temp.x = i % 2 ? offset.x : -offset.x;
        temp.y = i < 2 ? offset.y : -offset.y;
        Vector2 pos = CENTER + temp;

        renderTextures[i] = new Quad(CENTER * 2);
        renderTextures[i]->SetPos(pos);
        renderTextures[i]->UpdateWorld();
        renderTextures[i]->GetMaterial()->SetTexture(targetTexture);
        ///renderTextures[i]->GetMaterial()->SetShader(L"Shaders/Filter.hlsl");
    }   

    renderTextures[0]->GetMaterial()->SetShader(L"Shaders/Filter.hlsl");
    renderTextures[1]->GetMaterial()->SetShader(L"Shaders/Outline.hlsl");

    valueBuffer = new IntValueBuffer();

}

RenderTargetScene::~RenderTargetScene()
{
    delete bg;
    delete robot;
    delete valueBuffer;
}

void RenderTargetScene::Update()
{
    robot->Update();
}

void RenderTargetScene::PreRender()
{
    renderTarget->Set();

    bg->Render();
    robot->Render();
}

void RenderTargetScene::Render()
{
    valueBuffer->SetPS(2);

    for(Quad* renderTexture : renderTextures)
        renderTexture->Render();
}

void RenderTargetScene::PostRender()
{
    ImGui::DragInt("Select", &valueBuffer->Get()[0]);
    ImGui::DragInt("Scale", &valueBuffer->Get()[1]);
}
