#include "Framework.h"

Map::Map(string name)
	:name(name)
{
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

void Map::AddRoom(Room* room)
{
    rooms.push_back(room);
}

void Map::DeleteRoom(Room* room)
{
    auto it = find(rooms.begin(), rooms.end(), room);
    if (it != rooms.end())
    {
        delete* it;
        rooms.erase(it);
    }
}

void Map::Save(BinaryWriter& writer)
{
    // Save map name
    writer.String(name);

    // Save room count
    writer.UInt(rooms.size());

    // Save each room
    for (Room* room : rooms)
        room->Save(writer);
}

void Map::Load(BinaryReader& reader)
{
    name = reader.String();

    // Load room count
    UINT roomCount = reader.UInt();

    for (UINT i = 0; i < roomCount; ++i)
    {
        UINT roomWidth = reader.UInt();
        UINT roomHeight = reader.UInt();
        wstring roomBackGroundFile = reader.WString();

        Quad* backGround = new Quad(roomBackGroundFile);
        Room* room = new Room(roomWidth, roomHeight, backGround);
        room->SetSize(roomWidth, roomHeight);
        room->Load(reader);
        rooms.push_back(room);
    }
}
