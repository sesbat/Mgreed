#include "Framework.h"
#include "Room.h"

Room::Room(int width, int height, Quad* backGround)
    : width(width), height(height), backGround(backGround)
{
    grid.resize(height, vector<Tile*>(width, nullptr));
    backGround->SetPos(CENTER);
    backGround->UpdateWorld();
}

Room::~Room()
{
    for (auto& row : grid)
    {
        for (Tile* tile : row)
            delete tile;
    }
}

void Room::Update()
{
    for (auto& row : grid)
    {
        for (Tile* tile : row)
        {
            if (tile)
                tile->Update();
        }
    }
}

void Room::Render()
{
    backGround->Render();
    for (auto& row : grid)
    {
        for (Tile* tile : row)
        {
            if (tile)
                tile->Render();
        }
    }
}

void Room::SetTile(int x, int y, Tile* tile)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
    {
        if (grid[y][x])
            delete grid[y][x];
        grid[y][x] = tile;
    }
}

Tile* Room::GetTile(int x, int y)
{
    if (x >= 0 && x < width && y >= 0 && y < height)
        return grid[y][x];
    return nullptr;
}