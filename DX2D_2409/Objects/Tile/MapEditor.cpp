#include "Framework.h"

Vector2 MapEditor::selectFrame = Vector2();

MapEditor::MapEditor()
{
    SetTag("MapEditor");

    pos = { 50, 50 };
    UpdateWorld();

    CreateTiles();
    LoadTextures();

    EventManager::Get()->AddEvent("UpdateInstance", bind(&MapEditor::UpdateInstanceData, this));

    player = new SokobanPlayer();
}

MapEditor::~MapEditor()
{
    delete quad;
    delete instanceBuffer;

    for (EditTile* editTile : editTiles)
        delete editTile;
    for (CollisionTile* collisionTile : collisionTiles)
        delete collisionTile;

    delete player;
}



void MapEditor::Update()
{
    DragTile();
    PlaceCollisionTile();
    PlayerCollision();
    for (EditTile* editTile : editTiles)
        editTile->Update();
    for (CollisionTile* collisionTile : collisionTiles)
        collisionTile->Update();

    player->Update();
}
void MapEditor::PreRender()
{

}

void MapEditor::Render()
{
    instanceBuffer->Set(1);

    quad->GetMaterial()->Set();
    quad->GetMesh()->SetMesh();    

    deviceContext->DrawIndexedInstanced(6, editTiles.size(), 0, 0, 0);

    for (EditTile* editTile : editTiles)
        editTile->Render(); 

    for (CollisionTile* collisionTile : collisionTiles)
        collisionTile->Render();
    player->Render();
}

void MapEditor::Edit()
{
    Transform::Edit();

    RenderButtons();

    static char fileName[128] = "map_data.bin";
    ImGui::InputText("File Name", fileName, IM_ARRAYSIZE(fileName));

    if (ImGui::Button("Save Map"))
    {
        Save(fileName);
    }

    if (ImGui::Button("Load Map"))
    {
        Load(fileName);
    }
}

void MapEditor::Save(const string& filePath)
{
    ofstream fout(filePath, ios::binary);

    size_t instanceCount = instances.size();
    fout.write((char*)&instanceCount, sizeof(size_t));

    for (const InstanceData& instance : instances)
    {
        fout.write((char*)&instance, sizeof(InstanceData));
    }

    size_t collisionCount = collisionTiles.size();
    fout.write((char*)&collisionCount, sizeof(size_t));

    for (CollisionTile* tile : collisionTiles)
    {
        Vector2 pos = tile->GetPos();
        fout.write((char*)&pos, sizeof(Vector2));

        string textureFile = Utility::ToString(tile->GetImage()->GetMaterial()->GetTexture()->GetFile());
        size_t length = textureFile.size();
        fout.write((char*)&length, sizeof(size_t));
        fout.write(textureFile.c_str(), length);
    }

    fout.close();
}

void MapEditor::Load(const string& filePath)
{
    ifstream fin(filePath, ios::binary);

    size_t instanceCount;
    fin.read((char*)&instanceCount, sizeof(size_t));

    instances.clear();
    for (size_t i = 0; i < instanceCount; ++i)
    {
        InstanceData instance;
        fin.read((char*)&instance, sizeof(InstanceData));
        instances.push_back(instance);
    }

    size_t collisionCount;
    fin.read((char*)&collisionCount, sizeof(size_t));

    collisionTiles.clear();
    for (size_t i = 0; i < collisionCount; ++i)
    {
        Vector2 pos;
        fin.read((char*)&pos, sizeof(Vector2));

        size_t length;
        fin.read((char*)&length, sizeof(size_t));
        string textureFile(length, '\0');
        fin.read(&textureFile[0], length);

        CollisionTile* tile = new CollisionTile(Utility::ToWString(textureFile));
        tile->SetPos(pos);
        tile->SetParent(this);
        tile->UpdateWorld();

        collisionTiles.push_back(tile);
    }

    fin.close();
    UpdateInstanceData();
}

void MapEditor::DragTile()
{
    if (collisionMode) return;
    static Vector2 dragStart;
    bool isClick = false;

    if (KEY->Down(VK_LBUTTON))
    {
        dragStart = mousePos;
    }

    // 드래그 중
    if (KEY->Press(VK_LBUTTON))
    {
        for (EditTile* editTile : editTiles)
        {
            Vector2 tilePos = editTile->GetPos();

            if (editTile->Right() >= min(dragStart.x, mousePos.x) &&
                editTile->Left() <= max(dragStart.x, mousePos.x) &&
                editTile->Top() >= min(dragStart.y, mousePos.y) &&
                editTile->Bottom() <= max(dragStart.y, mousePos.y))
            {
                editTile->SetDragging(true);
            }
            else
            {
                editTile->SetDragging(false);
            }
        }
    }

    // 드래그 종료
    if (KEY->Up(VK_LBUTTON))
    {
        for (EditTile* editTile : editTiles)
        {
            if (editTile->IsDragging())
            {
                int index = find(editTiles.begin(), editTiles.end(), editTile) - editTiles.begin();
                instances[index].curFrame = selectFrame; 
            }
        }

        UpdateInstanceData();
    }
}

void MapEditor::CreateTiles()
{
    Vector2 maxFrame = { 13, 8 };

    quad = new Quad(L"Textures/Tile/tiles.png", Vector2(),
        Vector2(1 / maxFrame));
    quad->GetMaterial()->SetShader(L"Shaders/Instancing.hlsl");
    
    Vector2 tileSize = quad->GetSize();

    UINT size = width * height;

    instances.resize(size);
    editTiles.reserve(size);
    collisionTiles.reserve(size);
    for (int y = 0; y < height; y++)
    {
        for (int x = 0; x < width; x++)
        {
            int index = y * width + x;

            EditTile* editTile = new EditTile(tileSize, &instances[index]);
            editTile->SetPos(tileSize * Vector2(x, y));
            editTile->SetParent(this);
            editTile->UpdateWorld();
            instances[index].transform = XMMatrixTranspose(editTile->GetWorld());
            instances[index].curFrame = { 12, 6 };
            instances[index].maxFrame = maxFrame;
            editTiles.push_back(editTile);

            /*CollisionTile* collisionTile = new CollisionTile(L"Textures/Tile/Collision/block_01.png");
            collisionTile->SetPos(tileSize * Vector2(x, y));
            collisionTile->SetParent(this);
            collisionTile->UpdateWorld();
            collisionTiles.push_back(collisionTile);*/
        }
    }

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), size);
}

void MapEditor::LoadTextures()
{
    WIN32_FIND_DATA findData;

    HANDLE handle = FindFirstFile(L"Textures/Tile/Ground/*.png", &findData);

    bool result = true;
    wstring path = L"Textures/Tile/Ground/";

    while (result)
    {
        Texture* texture = Texture::Add(path + findData.cFileName);

        EditTextures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }

    handle = FindFirstFile(L"Textures/Tile/Collision/*.png", &findData);

    result = true;
    path = L"Textures/Tile/Collision/";

    while (result)
    {
        Texture* texture = Texture::Add(path + findData.cFileName);

        collisionTextures.push_back(texture);

        result = FindNextFile(handle, &findData);
    }
}

void MapEditor::RenderButtons()
{
    UINT width = 5;

    if (ImGui::TreeNode("EditTile Buttons"))
    {
        int count = 0;

        Vector2 startFrame = { 10, 6 };

        for (Texture* texture : EditTextures)
        {
            string key = "Ground" + to_string(count);
            if (ImGui::ImageButton(key.c_str(), (ImTextureID)texture->GetSRV(), ImVec2(50, 50)))
            {
                int x = count % 3;
                int y = count / 3;

                selectFrame = startFrame + Vector2(x, y);
            }

            count++;

            if (count % 5)
                ImGui::SameLine();
        }
        ImGui::NewLine();
        ImGui::TreePop();
    }

    if (ImGui::TreeNode("CollisionTile Buttons"))
    {
        int count = 0;

        for (Texture* texture : collisionTextures)
        {
            string key = "Collision" + to_string(count);
            if (ImGui::ImageButton(key.c_str(), (ImTextureID)texture->GetSRV(), ImVec2(50, 50)))
            {
                collisionSelectedTexture = texture; 
                collisionMode = true; 
            }

            count++;

            if (count % 5)
                ImGui::SameLine();
        }
        ImGui::NewLine();
        /*if (ImGui::Button("Place Collision Tile"))
        {
            collisionMode = true;
        }*/

        ImGui::TreePop();
    }
}

void MapEditor::PlaceCollisionTile()
{
    if (!collisionMode || !collisionSelectedTexture) return; 

    if (KEY->Press(VK_RBUTTON))
    {
        for (EditTile* tile : editTiles)
        {
            if (tile->IsPointCollision(mousePos))
            {
                bool exists = false;
                for (CollisionTile* collisionTile : collisionTiles)
                {
                    if (collisionTile->GetPos() == tile->GetPos())
                    {
                        exists = true;
                        break;
                    }
                }

                if (!exists)
                {
                    CollisionTile* collisionTile = new CollisionTile(collisionSelectedTexture->GetFile());
                    collisionTile->SetPos(tile->GetPos());
                    collisionTile->SetParent(this);
                    collisionTile->UpdateWorld();

                    collisionTiles.push_back(collisionTile);
                }
                break;
            }
        }
    }

    if (KEY->Up(VK_RBUTTON))
        collisionMode = false;
}

void MapEditor::UpdateInstanceData()
{
    instanceBuffer->Update(instances.data(), instances.size());
}

void MapEditor::PlayerCollision()
{
    for (auto tile : collisionTiles)
    {
        Vector2 overlap;
        if (tile->IsCollision(player , &overlap))
        {
            if (overlap.x > overlap.y)
            {
                if (player->GetPos().y > tile->GetPos().y)
                    player->Translate(Vector2::Up() * overlap.y);
                if (player->GetPos().y < tile->GetPos().y)
                    player->Translate(Vector2::Down() * overlap.y);
            }
            else
            {
                if (player->GetPos().x > tile->GetPos().x)
                    player->Translate(Vector2::Right() * overlap.x);
                if (player->GetPos().x < tile->GetPos().x)
                    player->Translate(Vector2::Left() * overlap.x);
            }
        }
    }
}

