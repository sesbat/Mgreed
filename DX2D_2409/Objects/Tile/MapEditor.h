#pragma once
#include "Framework.h"

class MapEditor : public Transform
{
private:
    enum Mode
    {
        INSERT,REMOVE
    };
public:
    MapEditor();
    ~MapEditor();

    void Update();
    void Render();
    void Edit();

    void Save(const string& filePath);
    void Load(const string& filePath);

    static Vector2 GetSelectFrame() { return selectFrame; }
    Room* GetSelectedRoom() { return selectedRoom; }
private:
    void LoadTileQuads();

    void AddNewMap(const string& mapName);
    void DeleteSeletedMap();

    void RenderMode();
    void RenderMapSelection();
    void RenderRoomSelection();
    void RenderTileSelection();
    void PlaceTile();
private:
    UINT roomWidth = 10, roomHeight = 10;

    vector<Map*> maps;              
    Map* selectedMap = nullptr;     
    Room* selectedRoom = nullptr;    
    Tile* selectedTile = nullptr;
    //Quad* selectBackGroundObject = nullptr;
    bool isDragging = false;

    Mode mode = INSERT;
    //instance
    vector<EditTile*> editTiles;
    vector<Quad*> editTileQuads;
    //vector<Quad*> backgroundObjectQuads;

    vector<Tile*> tiles;
    vector<Tile*> objectTiles;
    bool isCollisionTile = false;

    static Vector2 selectFrame;
    int selectIndex = 0;
};