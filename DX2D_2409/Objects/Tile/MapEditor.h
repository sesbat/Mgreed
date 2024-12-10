#pragma once
#include "Framework.h"

class MapEditor : public Transform
{
public:
    MapEditor();
    ~MapEditor();

    void Update();
    void Render();
    void Edit();

private:
    Vector2 tileSize = { 50,50 };

    vector<Map*> maps;              
    Map* selectedMap = nullptr;     
    Room* selectedRoom = nullptr;    
    Tile* selectedTile = nullptr;   

    vector<SpriteData> tileSprites;  
    Texture* tileTexture = nullptr;  

    int selectedTileIndex = -1;     

    void RenderMapSelection();
    void RenderRoomSelection();
    void RenderTileSelection();
    void PlaceTile(int x, int y);
};