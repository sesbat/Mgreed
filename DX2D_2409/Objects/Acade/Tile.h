#pragma once

class Tile : public ImageObject
{
public:
    Tile(wstring textureFile, Vector2 startUV, Vector2 endUV)
        : ImageObject(textureFile, startUV, endUV) {}

private:

};