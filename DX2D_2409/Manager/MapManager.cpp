#include "Framework.h"

MapManager* MapManager::instance = nullptr;

MapManager::MapManager() {}

MapManager::~MapManager()
{
    delete currentMap;
    for (Map* map : savedMaps)
        delete map;
}

void MapManager::SaveCurrentMap(const string& filePath)
{
    if (!currentMap)
        return;

    BinaryWriter writer(filePath);
    currentMap->Save(writer);
}

void MapManager::LoadMap(const string& filePath)
{
    if (currentMap)
    {
        delete currentMap;
        currentMap = nullptr;
    }

    BinaryReader reader(filePath);
    currentMap = new Map(filePath);
    currentMap->Load(reader);
}

void MapManager::GenerateRandomMap(int roomCount, int minWidth, int maxWidth, int minHeight, int maxHeight)
{
    if (currentMap)
        delete currentMap;

    currentMap = new Map("RandomMap");

    for (int i = 0; i < roomCount; ++i)
    {
        int width = rand() % (maxWidth - minWidth + 1) + minWidth;
        int height = rand() % (maxHeight - minHeight + 1) + minHeight;

        wstring backGroundFile = L"Textures/Maple/Background/Henesis.png";
        Room* room = new Room(width, height, new Quad(backGroundFile));
        currentMap->AddRoom(room);

        randomRooms.push_back(room);
    }
}

void MapManager::SetCurrentMap(Map* map)
{
    if (currentMap)
        delete currentMap;

    currentMap = map;
}

void MapManager::AddRoomToMap(int width, int height, const wstring& backGroundFile)
{
    if (!currentMap)
        return;

    Room* newRoom = new Room(width, height, new Quad(backGroundFile));
    currentMap->AddRoom(newRoom);
}

Room* MapManager::GetNextRoom()
{
    if (randomRooms.empty())
        return nullptr;

    int randomIndex = rand() % randomRooms.size();
    Room* nextRoom = randomRooms[randomIndex];

    // 이미 사용된 방은 제거 (선택적)
    //randomRooms.erase(randomRooms.begin() + randomIndex);
    return nextRoom;
}