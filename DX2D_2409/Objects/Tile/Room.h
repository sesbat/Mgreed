#pragma once
#include "Framework.h"

class Room : public Transform
{
public:
    Room(int width, int height, Quad* backGround);
    Room();
    ~Room();

    void Update();
    void Render();

    void SetSize(int width, int height) { this->width = width, this->height = height; }

    void SetEditTile(int x, int y, Vector2 frame);
    void SetCollisionTile(int x, int y, wstring file);

    EditTile* GetEditTile(int x, int y) { return editTiles[y][x]; }
    Tile* GetCollisionTile(int x, int y) { return collisionTiles[y][x]; }

    const vector<vector<EditTile*>>& GetEditTiles() const { return editTiles; }
    const vector<vector<Tile*>>& GetCollisionTiles() const { return collisionTiles; }

    int GetWidth() const { return width; }
    int GetHeight() const { return height; }
    Vector2 GetTileSize() const { return tileSize; }
    Quad* GetBackground() const { return backGround; }

    void Save(BinaryWriter& writer);
    void Load(BinaryReader& reader);
private:
    void CreateTiles();
    void UpdateInstanceData();

private:
    int width, height;
    Vector2 tileSize;

    Quad* backGround;

    Quad* quad = nullptr;
    vector<InstanceData> instances;
    VertexBuffer* instanceBuffer;

    vector<vector<EditTile*>> editTiles;        
    vector<vector<Tile*>> collisionTiles; 
};