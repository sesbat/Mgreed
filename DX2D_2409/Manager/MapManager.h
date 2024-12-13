#pragma once

class MapManager : public Singleton<MapManager>
{
public:
    void SaveCurrentMap(const string& filePath);
    void LoadMap(const string& filePath);

    void GenerateRandomMap(int roomCount, int minWidth, int maxWidth, int minHeight, int maxHeight);
    Map* GetCurrentMap() const { return currentMap; }
    void SetCurrentMap(Map* map);

    void AddRoomToMap(int width, int height, const wstring& backGroundFile);

    Room* GetNextRoom();
private:
    MapManager();
    ~MapManager();

private:
    static MapManager* instance;
    Map* currentMap = nullptr;

    vector<Map*> savedMaps;
    vector<Room*> randomRooms; 
};
