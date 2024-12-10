#pragma once
#include "Framework.h"

using namespace tinyxml2;

class TileLoader
{
public:
    TileLoader(const string& xmlFilePath);
    ~TileLoader() {}

    const vector<SpriteData>& GetSprites() const { return sprites; }
    const string& GetTexturePath() const { return texturePath; }

private:
    string texturePath;           
    vector<SpriteData> sprites;   

    void LoadXML(const string& filePath);
};