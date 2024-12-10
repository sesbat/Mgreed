#pragma once

class Tile : public ImageObject
{
public:
    Tile(wstring file, Vector2 startUV, Vector2 endUV);
    ~Tile();
};