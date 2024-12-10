#pragma once
#include "Framework.h"

class Room : public Transform
{
public:
    Room(int width, int height, Quad* backGround);
    ~Room();

    void Update();
    void Render();

    void SetTile(int x, int y, Tile* tile);
    Tile* GetTile(int x, int y);

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }

private:
    int width, height;
    vector<vector<Tile*>> grid;
    Quad* backGround;
};
