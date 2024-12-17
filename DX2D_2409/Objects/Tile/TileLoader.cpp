#include "Framework.h"

TileLoader::TileLoader(const string& xmlFilePath)
{
    LoadXML(xmlFilePath);
}

void TileLoader::LoadXML(const string& filePath)
{
    tinyxml2::XMLDocument doc;
    XMLError result = doc.LoadFile(filePath.c_str());
    if (result != XML_SUCCESS)
    {
        return;
    }

    XMLElement* root = doc.FirstChildElement("TextureAtlas");
    if (!root)
    {
        return;
    }

    texturePath = root->Attribute("imagePath");

    for (XMLElement* sprite = root->FirstChildElement("sprite"); sprite; sprite = sprite->NextSiblingElement("sprite"))
    {
        SpriteData data;
        data.name = sprite->Attribute("n");
        data.x = sprite->IntAttribute("x");
        data.y = sprite->IntAttribute("y");
        data.width = sprite->IntAttribute("w");
        data.height = sprite->IntAttribute("h");
        data.pivotX = sprite->FloatAttribute("pX");
        data.pivotY = sprite->FloatAttribute("pY");

        sprites.push_back(data);
    }
}
