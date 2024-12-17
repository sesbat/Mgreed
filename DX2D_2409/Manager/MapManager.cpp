#include "Framework.h"

MapManager* MapManager::instance = nullptr;

void MapManager::CheckCollision()
{
	if (!selectedMap) return;
}

MapManager::~MapManager()
{
	for (Map* map : maps)
		delete map;
}

void MapManager::SaveAllMaps(const string& filePath)
{
	BinaryWriter writer(filePath);
	writer.UInt(maps.size());

	for (Map* map : maps)
		map->Save(writer);
}

void MapManager::LoadAllMaps(const string& filePath)
{
	BinaryReader reader(filePath);

	for (Map* map : maps)
		delete map;
	maps.clear();

	UINT mapCount = reader.UInt();
	for (UINT i = 0; i < mapCount; ++i)
	{
		Map* map = new Map(filePath);
		map->Load(reader);
		maps.push_back(map);
	}

	if (!maps.empty())
		selectedMap = maps.front();
}

Map* MapManager::CreateNewMap(const string& name)
{
	Map* newMap = new Map(name);
	maps.push_back(newMap);
	return newMap;
}

void MapManager::DeleteMap(Map* map)
{
	auto it = find(maps.begin(), maps.end(), map);
	if (it != maps.end())
	{
		delete* it;
		maps.erase(it);
	}

	if (!maps.empty())
		selectedMap = maps.front();
	else
		selectedMap = nullptr;
}

Map* MapManager::GetMapByName(const string& name)
{
	for (Map* map : maps)
	{
		if (map->GetName() == name)
			return map;
	}
	return nullptr;
}