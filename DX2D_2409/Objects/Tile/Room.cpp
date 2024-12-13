#include "Framework.h"
#include "Room.h"

Room::Room(int width, int height, Quad* backGround)
    : width(width), height(height), backGround(backGround)
{
    editTiles.resize(height, vector<EditTile*>(width, nullptr));
    collisionTiles.resize(height, vector<Tile*>(width, nullptr));

    CreateTiles();
    EventManager::Get()->AddEvent("UpdateInstance", bind(&Room::UpdateInstanceData, this));

    backGround->SetPos(CENTER);
    backGround->UpdateWorld();
}

Room::Room()
    :width(10), height(10), backGround(nullptr)
{
    editTiles.resize(height, vector<EditTile*>(width, nullptr));
    collisionTiles.resize(height, vector<Tile*>(width, nullptr));
    CreateTiles();
}

Room::~Room()
{
    delete backGround;
    backGround = nullptr;
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (editTiles[y][x])
                delete editTiles[y][x];
            if (collisionTiles[y][x])
                delete collisionTiles[y][x];
        }
    }
}

void Room::Update()
{
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (editTiles[y][x])
                editTiles[y][x]->Update();
            if (collisionTiles[y][x])
                collisionTiles[y][x]->Update();
        }
    }
}

void Room::Render()
{
    if (backGround)
        backGround->Render();

    instanceBuffer->Set(1);

    quad->GetMaterial()->Set();
    quad->GetMesh()->SetMesh();

    deviceContext->DrawIndexedInstanced(6, width * height + 50, 0, 0, 0);

    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            if (editTiles[y][x])
                editTiles[y][x]->Render();
            if (collisionTiles[y][x])
                collisionTiles[y][x]->Render();
        }
    }
}

void Room::SetEditTile(int x, int y, Vector2 frame)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    if (!editTiles[y][x])
        return;

    editTiles[y][x]->SetInstanceData(frame);
    UpdateInstanceData();
}

void Room::SetCollisionTile(int x, int y, wstring file)
{
    if (x < 0 || x >= width || y < 0 || y >= height)
        return;

    if (collisionTiles[y][x])
    {
        if (collisionTiles[y][x]->GetImage()->GetMaterial()->GetTexture()->GetFile() == file)
            return;

        delete collisionTiles[y][x];
        collisionTiles[y][x] = nullptr;
    }
    collisionTiles[y][x] = new Tile(file);
    collisionTiles[y][x]->SetPos(tileSize * Vector2(x, y));
    collisionTiles[y][x]->SetParent(this);
    collisionTiles[y][x]->UpdateWorld();
}

void Room::Save(BinaryWriter& writer)
{
    writer.UInt(width);
    writer.UInt(height);

    writer.WString(backGround->GetMaterial()->GetTexture()->GetFile());
    // Save Edit Tiles
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2 frame = editTiles[y][x] ? editTiles[y][x]->GetInstanceData()->curFrame : Vector2(-1, -1);
            writer.Vector(frame);
        }
    }

    // Save Collision Tiles
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            wstring file = collisionTiles[y][x] ? collisionTiles[y][x]->GetImage()->GetMaterial()->GetTexture()->GetFile() : L"";
            writer.WString(file);
        }
    }
}

void Room::Load(BinaryReader& reader)
{
   /* width = reader.UInt();
    height = reader.UInt();*/

    // Resize the vectors
    editTiles.resize(height, vector<EditTile*>(width, nullptr));
    collisionTiles.resize(height, vector<Tile*>(width, nullptr));

    // Load Edit Tiles
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            Vector2 frame = reader.Vector();
            if (frame.x >= 0 && frame.y >= 0)
            {
                editTiles[y][x]->SetInstanceData(frame);
            }
        }
    }
    UpdateInstanceData();

    // Load Collision Tiles
    for (int y = 0; y < height; ++y)
    {
        for (int x = 0; x < width; ++x)
        {
            wstring file = reader.WString();
            if (!file.empty())
            {
                collisionTiles[y][x] = new Tile(file);
                collisionTiles[y][x]->SetPos(tileSize * Vector2(x, y));
                collisionTiles[y][x]->SetParent(this);
                //collisionTiles[y][x]->UpdateWorld();
            }
        }
    }
}

void Room::CreateTiles()
{
    Vector2 maxFrame = { 13, 8 };

    quad = new Quad(L"Textures/Tile/tiles.png", Vector2(),
        Vector2(1 / maxFrame));
    quad->GetMaterial()->SetShader(L"Shaders/Instancing.hlsl");

    tileSize = quad->GetSize();

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
            
            editTiles[y][x] = editTile;
            collisionTiles[y][x] = nullptr;
        }
    }

    instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), size);
}

void Room::UpdateInstanceData()
{
	instanceBuffer->Update(instances.data(), instances.size());
}
