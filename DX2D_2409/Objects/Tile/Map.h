#pragma once

class Map
{
public:
    Map(string name, int roomWidth, int roomHeight, int numRooms, Quad* roomImage);
    ~Map();

    void Update();
    void Render();

    Room* GetRoom(int index);
    const string& GetName() const { return name; }
    vector<Room*> GetRooms() const { return rooms; }
private:
    string name;
    vector<Room*> rooms;
};
