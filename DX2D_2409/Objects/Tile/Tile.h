#pragma once

class Tile : public ImageObject
{
public:
    enum TileType
    {
        COLLISION, OBJECT, PLATFORM
    };
public:
    Tile(wstring file);
    ~Tile();

    TileType GetType() { return type; }
protected:
    TileType type = COLLISION;
};