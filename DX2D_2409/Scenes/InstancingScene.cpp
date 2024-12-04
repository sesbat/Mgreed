#include "Framework.h"
#include "InstancingScene.h"

InstancingScene::InstancingScene()
{
    //quads.resize(SIZE);
    //FOR(SIZE)
    //{
    //    Quad* quad = new Quad(L"Textures/Acade/mario.png", Vector2(),
    //        Vector2(1.0f/8.0f, 1.0f/4.0f));
    //    float x = GameMath::Random(0, SCREEN_WIDTH);
    //    float y = GameMath::Random(0, SCREEN_HEIGHT);
    //    quad->SetPos(x, y);
    //
    //    x = GameMath::Random(0.1f, 1.0f);
    //    y = GameMath::Random(0.1f, 1.0f);
    //
    //    //quad->SetScale(x, y);  
    //    quad->UpdateWorld();
    //
    //    quads[i] = quad;
    //}

    quad = new Quad(L"Textures/Tiles/tile1.png");
    quad->GetMaterial()->SetShader(L"Shaders/Instancing.hlsl");

    instances.resize(WIDTH * HEIGHT);

    for (Matrix& instance : instances)
    {
        Transform transform;
        float x = GameMath::Random(0, SCREEN_WIDTH);
        float y = GameMath::Random(0, SCREEN_HEIGHT);
        transform.SetPos(x, y);

        //x = Random(0.1f, 1.0f);
        //y = Random(0.1f, 1.0f);
        //
        //transform.SetLocalScale(x, y);
        transform.UpdateWorld();

        instance = XMMatrixTranspose(transform.GetWorld());
        //instance = XMMatrixIdentity();
    }

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), WIDTH * HEIGHT);
}

InstancingScene::~InstancingScene()
{
    //for (Quad* quad : quads)
    //    delete quad;

    delete quad;
    delete instanceBuffer;
}

void InstancingScene::Update()
{
}

void InstancingScene::Render()
{
    //for (Quad* quad : quads)
    //    quad->Render();

    instanceBuffer->Set(1);

    quad->GetMaterial()->Set();
    quad->GetMesh()->SetMesh();
    //quad->SetWorld();

    deviceContext->DrawIndexedInstanced(6, WIDTH * HEIGHT, 0, 0, 0);
}

void InstancingScene::PostRender()
{
}
