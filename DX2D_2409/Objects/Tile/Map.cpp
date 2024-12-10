#include "Framework.h"

Map::Map(string name, int roomWidth, int roomHeight, int numRooms, Quad* roomImage)
    :name(name)
{
    for (int i = 0; i < numRooms; ++i)
        rooms.push_back(new Room(roomWidth, roomHeight, roomImage));
}

Map::~Map()
{
    for (Room* room : rooms)
        delete room;
    rooms.clear();
}

void Map::Update()
{
    for (Room* room : rooms)
        room->Update();
}

void Map::Render()
{
    for (Room* room : rooms)
        room->Render();
}

Room* Map::GetRoom(int index)
{
    if (index >= 0 && index < rooms.size())
        return rooms[index];
    return nullptr;
}
