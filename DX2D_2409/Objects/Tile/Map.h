#pragma once

class Player;
class Map : public Transform
{
public:
    Map(string name);
    ~Map();

    void Update();
    void Render();

    void AddRoom(Room* room);
    void DeleteRoom(Room* room);

    void SetCurrentRoom(Room* room) { currentRoom = room; }
    Room* GetCurrentRoom() { return currentRoom; }

    const vector<Room*>& GetRooms() const { return rooms; }
    string GetName() const { return name; }

    void Save(BinaryWriter& writer);
    void Load(BinaryReader& reader);
private:
    string name;
    vector<Room*> rooms;
    Room* currentRoom = nullptr;
};
