#pragma once

class MapManager : public Singleton<MapManager>
{
public:
    friend Singleton;
    void SaveAllMaps(const string& filePath);
    void LoadAllMaps(const string& filePath);

    Map* CreateNewMap(const string& name);
    void DeleteMap(Map* map);

    const vector<Map*>& GetMaps() const { return maps; }
    Map* GetMapByName(const string& name);
    Map* GetSelectedMap() const { return selectedMap; }

    void SetSelectedMap(Map* map) { selectedMap = map; }

    void CheckCollision();
private:
    MapManager() {}
    ~MapManager();

    vector<Map*> maps;
    Map* selectedMap = nullptr;
};
