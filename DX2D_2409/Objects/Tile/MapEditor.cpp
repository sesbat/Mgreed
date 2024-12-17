#include "Framework.h"
#include "MapEditor.h"

Vector2 MapEditor::selectFrame = Vector2();

MapEditor::MapEditor()
{
	tag = "MapEditor";
	pos = 50, 50;
	UpdateWorld();
	LoadTileQuads();
	//EventManager::Get()->AddEvent("UpdateInstance", bind(&MapEditor::UpdateInstanceData, this));

	//Quad* image = new Quad(L"Textures/Maple/Background/Henesis.png");
}

MapEditor::~MapEditor()
{
	for (Map* map : maps)
		delete map;
	maps.clear();
}

void MapEditor::Update()
{
	if (selectedRoom)
	{
		
		if (KEY->Press(VK_LBUTTON))
		{
			PlaceTile();
			//selectedRoom->Update();
		}
	}
}

void MapEditor::Render()
{
	if (selectedRoom)
	{
		selectedRoom->Render();
	}
}

void MapEditor::Edit()
{
	RenderMapSelection();
	RenderRoomSelection();
	RenderTileSelection();
	RenderMode();

	static char fileName[128] = "map_data.bin";
	ImGui::InputText("File Name", fileName, IM_ARRAYSIZE(fileName));

	if (ImGui::Button("Save All Maps"))
	{
		MapManager::Get()->SaveAllMaps(fileName);
	}

	if (ImGui::Button("Load All Maps"))
	{
		MapManager::Get()->LoadAllMaps(fileName);
	}
}

void MapEditor::Save(const string& filePath)
{
	BinaryWriter writer(filePath);

	// Save number of maps
	writer.UInt(maps.size());

	// Save each map
	for (Map* map : maps)
	{
		map->Save(writer);
	}
}

void MapEditor::Load(const string& filePath)
{
	BinaryReader reader(filePath);

	// Clear existing maps
	for (Map* map : maps)
		delete map;
	maps.clear();

	// Load number of maps
	UINT mapCount = reader.UInt();

	// Load each map
	for (UINT i = 0; i < mapCount; ++i)
	{
		Map* map = new Map(filePath);
		map->Load(reader);
		maps.push_back(map);
	}

	if (!maps.empty())
		selectedMap = maps.front();
}

void MapEditor::LoadTileQuads()
{
	WIN32_FIND_DATA findData;

	HANDLE handle = FindFirstFile(L"Textures/Dungreed/Tiles/BackGroundTile/*.png", &findData);
	bool result = true;
	wstring path = L"Textures/Dungreed/Tiles/BackGroundTile/";

	while (result)
	{
		//Texture* texture = Texture::Add(path + findData.cFileName);
		Quad* image = new Quad(path + findData.cFileName);

		editTileQuads.push_back(image);

		result = FindNextFile(handle, &findData);
	}

	handle = FindFirstFile(L"Textures/Dungreed/Tiles/Collision/*.png", &findData);
	result = true;
	path = L"Textures/Dungreed/Tiles/Collision/";
	while (result)
	{
		//Texture* texture = Texture::Add(path + findData.cFileName);
		Tile* tile = new Tile(path + findData.cFileName);

		tiles.push_back(tile);

		result = FindNextFile(handle, &findData);
	}

	//handle = FindFirstFile(L"Textures/Dungreed/Tiles/BackGroundObject/*.png", &findData);
	//result = true;
	//path = L"Textures/Dungreed/Tiles/BackGroundObject/";
	//while (result)
	//{
	//	//Texture* texture = Texture::Add(path + findData.cFileName);
	//	Quad* tile = new Quad(path + findData.cFileName);

	//	backgroundObjectQuads.push_back(tile);

	//	result = FindNextFile(handle, &findData);
	//}
}

void MapEditor::AddNewMap(const string& mapName)
{
	Map* newMap = new Map(mapName);
	maps.push_back(newMap);
}

void MapEditor::DeleteSeletedMap()
{
	if (!selectedMap) return;

	// Find and delete the selected map
	auto it = std::find(maps.begin(), maps.end(), selectedMap);
	if (it != maps.end())
	{
		delete* it;
		maps.erase(it);
		selectedMap = nullptr;

		if (!maps.empty())
			selectedMap = maps.front();
	}
}

void MapEditor::RenderMode()
{
	if (ImGui::TreeNode("Select Mode"))
	{
		if (ImGui::Button("Insert"))
		{
			mode = INSERT;
		}

		if (ImGui::Button("Remove"))
		{
			mode = REMOVE;
		}
		ImGui::NewLine();
		ImGui::TreePop();
	}
}

void MapEditor::RenderMapSelection()
{
	if (ImGui::TreeNode("Select Map"))
	{
		const vector<Map*>& maps = MapManager::Get()->GetMaps();
		for (size_t i = 0; i < maps.size(); ++i)
		{
			if (ImGui::Selectable(maps[i]->GetName().c_str(), maps[i] == MapManager::Get()->GetSelectedMap()))
			{
				MapManager::Get()->SetSelectedMap(maps[i]);
				selectedMap = maps[i];
				selectedRoom = nullptr;
			}
		}

		static char newMapName[128] = "NewMap";
		ImGui::InputText("New Map Name", newMapName, IM_ARRAYSIZE(newMapName));

		if (ImGui::Button("Add New Map"))
		{
			selectedMap = MapManager::Get()->CreateNewMap(newMapName);
			selectedRoom = nullptr;
		}

		if (ImGui::Button("Delete Selected Map"))
		{
			if (selectedMap)
			{
				MapManager::Get()->DeleteMap(selectedMap);
				selectedMap = MapManager::Get()->GetSelectedMap();
				selectedRoom = nullptr;
			}
		}
		ImGui::TreePop();
	}
}

void MapEditor::RenderRoomSelection()
{
	if (!selectedMap)
		return;

	if (ImGui::TreeNode("Select Room"))
	{
		const vector<Room*>& rooms = selectedMap->GetRooms();

		for (size_t i = 0; i < rooms.size(); ++i)
		{
			string roomLabel = "Room " + to_string(i + 1);
			if (ImGui::Selectable(roomLabel.c_str(), rooms[i] == selectedRoom))
			{
				MapManager::Get()->GetSelectedMap()->SetCurrentRoom(rooms[i]);
				selectedRoom = rooms[i];
			}
		}

		static int newRoomWidth = 60;
		static int newRoomHeight = 25;

		ImGui::InputInt("New Room Width", &newRoomWidth);
		ImGui::InputInt("New Room Height", &newRoomHeight);

		if (ImGui::Button("Add New Room"))
		{
			selectedMap->AddRoom(new Room(newRoomWidth, newRoomHeight, new Quad(L"Textures/DunGreed/Tiles/BackGround/Sky_Day.png")));
		}

		if (ImGui::Button("Delete Selected Room"))
		{
			if (selectedRoom)
			{
				selectedMap->DeleteRoom(selectedRoom);
				selectedRoom = nullptr;
			}
		}

		ImGui::TreePop();
	}
}

void MapEditor::RenderTileSelection()
{
	if (!selectedRoom)
		return;
	UINT width = 5;
	if (ImGui::TreeNode("BackGroundTile"))
	{
		int count = 0;

		Vector2 startFrame = { 0, 0 };

		for (Quad* quad : editTileQuads)
		{
			string key = "BackGround Tiles" + to_string(count);
			if (ImGui::ImageButton(key.c_str(),
				(ImTextureID)quad->GetMaterial()->GetTexture()->GetSRV(), ImVec2(50, 50)))
			{
				mode = INSERT;
				int x = count % 38;
				selectIndex = count;
				isCollisionTile = false;
				selectFrame = startFrame + Vector2(x, 0);
			}

			count++;

			if (count % 5)
				ImGui::SameLine();
		}
		ImGui::NewLine();
		ImGui::TreePop();
	}
	if (ImGui::TreeNode("Collision Tiles"))
	{
		for (size_t i = 0; i < tiles.size(); ++i)
		{
			if (ImGui::ImageButton(("Collision " + to_string(i)).c_str(),
				(ImTextureID)tiles[i]->GetImage()->GetMaterial()->GetTexture()->GetSRV(), ImVec2(50, 50)))
			{
				mode = INSERT;
				selectIndex = i;
				isCollisionTile = true;
			}

			if ((i + 1) % 5 != 0)
				ImGui::SameLine();
		}
		ImGui::NewLine();
		ImGui::TreePop();
	}
}

void MapEditor::PlaceTile()
{
	if (!selectedRoom || selectIndex == -1)
		return;
	Vector2 tileSize =  selectedRoom->GetTileSize();
	Vector2 localMousePos = worldMousePos + tileSize / 2;
	int x = static_cast<int>(localMousePos.x / tileSize.x);
	int y = static_cast<int>(localMousePos.y / tileSize.y);

	Tile* tile = nullptr;

	if (mode == INSERT)
	{
		if (isCollisionTile)
		{
			/*switch (tiles[selectIndex]->GetType())
			{
			case Tile::COLLISION:
				tile = new CollisionTile(tiles[selectIndex]->GetImage()->GetMaterial()->GetTexture()->GetFile());
				break;
			case Tile::OBJECT:
				tile = new ObjectTile(tiles[selectIndex]->GetImage()->GetMaterial()->GetTexture()->GetFile());
				break;
			}*/
			selectedRoom->SetCollisionTile(x, y, tiles[selectIndex]->GetImage()->GetMaterial()->GetTexture()->GetFile());
		}
		else
		{
			selectedRoom->SetEditTile(x, y, selectFrame);
		}
	}
	else if (mode == REMOVE)
	{
		selectedRoom->RemoveTile(x, y);
	}
}
