#pragma once

class Map
{
public:
    Map(string name);
    ~Map();

    void AddRoom(Room* room);
    void DeleteRoom(Room* room);

    const vector<Room*>& GetRooms() const { return rooms; }
    string GetName() const { return name; }

    void Save(BinaryWriter& writer);
    void Load(BinaryReader& reader);
private:
    string name;
    vector<Room*> rooms;
};
