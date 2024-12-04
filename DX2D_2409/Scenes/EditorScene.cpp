#include "Framework.h"
#include "EditorScene.h"

EditorScene::EditorScene()
{
    imageObject = new ImageObject(L"Textures/Tiles/tile1.png");
    imageObject->GetImage()->GetMaterial()->SetShader(L"Shaders/Instancing.hlsl");
    tileSize = imageObject->GetImage()->GetSize();
    instances.resize(WIDTH * HEIGHT);

    /*for (int i = 0; i < 4; i++)
    {
        wstringstream ss;
        ss << L"Textures/Tiles/tile" << (i + 1) << L".png";
        Button* button = new Button(ss.str());
        button->SetPos(100 +i * 100, 50);
        tileButtons.push_back(button);
    }*/

    for (Matrix& instance : instances)
    {
        Transform transform;
        float x = GameMath::Random(0, SCREEN_WIDTH);
        float y = GameMath::Random(100, SCREEN_HEIGHT);
        transform.SetPos(x, y);

        transform.UpdateWorld();

        instance = XMMatrixTranspose(transform.GetWorld());
    }

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), WIDTH * HEIGHT);
}

EditorScene::~EditorScene()
{
	/*for (ImageObject* tile : tiles)
		delete tile;*/
    /*for (auto button : tileButtons)
        delete button;*/
    delete imageObject;
    delete instanceBuffer;
}

void EditorScene::Update()
{
    /*for (auto button : tileButtons)
        button->Update();*/
    //for (ImageObject* tile : tiles)
    //    tile->Update();

    //// 좌클릭으로 타일 추가
    //if (KEY->Down(VK_LBUTTON))
    //{
    //    ImageObject* tile = new ImageObject(L"Textures/Tiles/tile2.png");
    //    tile->SetPos(mousePos.x - tile->GetImage()->GetSize().x / 2, 
    //        mousePos.y - tile->GetImage()->GetSize().y / 2);
    //    tiles.push_back(tile);
    //}

    //// 우클릭으로 타일 제거
    //if (KEY->Down(VK_RBUTTON))
    //{
    //    for (auto it = tiles.begin(); it != tiles.end(); ++it)
    //    {
    //        if ((*it)->IsPointCollision(mousePos))
    //        {
    //            delete* it;
    //            tiles.erase(it);
    //            break;
    //        }
    //    }
    //}

    //타일 추가
    if (KEY->Down(VK_LBUTTON))
    {
        selectedTileIndex = -1;
        for (int i = 0; i < instances.size(); i++)
        {
            Transform transform;
            transform.SetWorld(instances[i]);
            Vector2 tilePos = Vector2(
                instances[i].r[0].m128_f32[3],
                instances[i].r[1].m128_f32[3]);
            if (mousePos.x > tilePos.x - tileSize.x * 0.5f &&
                mousePos.x < tilePos.x + tileSize.x * 0.5f &&
                mousePos.y > tilePos.y - tileSize.y * 0.5f &&
                mousePos.y < tilePos.y + tileSize.y * 0.5f)
            {
                selectedTileIndex = i;
                mouseOffset = tilePos - mousePos;
                isDragging = true;
                break;
            }
        }

        // 새 타일 추가
        if (selectedTileIndex == -1)
        {
            Transform transform;
            transform.SetPos(mousePos);
            transform.UpdateWorld();
            instances.push_back(XMMatrixTranspose(transform.GetWorld()));

            delete instanceBuffer;
            instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), instances.size());
        }
    }

    // 타일 이동
    if (KEY->Press(VK_LBUTTON) && isDragging && selectedTileIndex != -1)
    {
        Transform transform;
        transform.SetWorld(XMMatrixTranspose(instances[selectedTileIndex]));
        transform.SetPos(mousePos + mouseOffset);
        transform.UpdateWorld();
        instances[selectedTileIndex] = XMMatrixTranspose(transform.GetWorld());

        delete instanceBuffer;
        instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), instances.size());
    }

    // 드래그 종료
    if (KEY->Up(VK_LBUTTON))
    {
        isDragging = false;
        selectedTileIndex = -1;
    }

    // 타일 제거
    if (KEY->Down(VK_RBUTTON))
    {
        for (auto it = instances.begin(); it != instances.end(); ++it)
        {
            Transform transform;
            transform.SetWorld(*it);
            Vector2 tilePos = Vector2(
                (*it).r[0].m128_f32[3],
                (*it).r[1].m128_f32[3]);

            if (mousePos.x > tilePos.x - tileSize.x * 0.5f &&
                mousePos.x < tilePos.x + tileSize.x * 0.5f &&
                mousePos.y > tilePos.y - tileSize.y * 0.5f &&
                mousePos.y < tilePos.y + tileSize.y * 0.5f)
            {
                instances.erase(it);

                delete instanceBuffer;
                instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), instances.size());
                break;
            }
        }
    }
}

void EditorScene::Render()
{
    for (auto button : tileButtons)
        button->Render();
    instanceBuffer->Set(1);

    imageObject->GetImage()->GetMaterial()->Set();
    imageObject->GetImage()->GetMesh()->SetMesh();
    //quad->SetWorld();

    deviceContext->DrawIndexedInstanced(6, WIDTH * HEIGHT * 2, 0, 0, 0);
    /*for (ImageObject* tile : tiles)
        tile->Render();*/
}

void EditorScene::PostRender()
{
}

void EditorScene::SaveMap(string filePath)
{
    ofstream fout(filePath, ios::binary);
    for (const Matrix& instance : instances)
    {
        Transform transform;
        transform.SetWorld(XMMatrixTranspose(instance));
        Vector2 pos = transform.GetPos();
        fout.write((char*)&pos, sizeof(Vector2));
    }
    fout.close();
}

void EditorScene::LoadMap(string filePath)
{
    ifstream fin(filePath, ios::binary);
    instances.clear();
    while (!fin.eof())
    {
        Vector2 pos;
        fin.read((char*)&pos, sizeof(Vector2));
        if (fin.eof()) break;

        Transform transform;
        transform.SetPos(pos);
        transform.UpdateWorld();
        instances.push_back(XMMatrixTranspose(transform.GetWorld()));
    }
    fin.close();

    // 인스턴스 버퍼 업데이트
    delete instanceBuffer;
    instanceBuffer = new VertexBuffer(instances.data(), sizeof(Matrix), instances.size());
}