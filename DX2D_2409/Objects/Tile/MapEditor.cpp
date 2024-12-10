#include "Framework.h"
#include "MapEditor.h"

MapEditor::MapEditor()
{
	TileLoader loader("Textures/Maple/GroundTile/HenesisGround.xml");
	tileSprites = loader.GetSprites();

	Quad* image = new Quad(L"Textures/Maple/Background/Henesis.png");
	maps.push_back(new Map("Grassland", 10, 10, 3, image));
	maps.push_back(new Map("Desert", 15, 15, 5, image));
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
		selectedRoom->Update();

	if (KEY->Down(VK_LBUTTON))
	{
		int x = static_cast<int>(mousePos.x / tileSize.x);
		int y = static_cast<int>(mousePos.y / tileSize.y);
		PlaceTile(x, y);
	}
}

void MapEditor::Render()
{
	if (selectedRoom)
		selectedRoom->Render();
}

void MapEditor::Edit()
{
	RenderMapSelection();
	RenderRoomSelection();
	RenderTileSelection();
}

void MapEditor::RenderMapSelection()
{
	if (ImGui::TreeNode("Select Map"))
	{
		for (size_t i = 0; i < maps.size(); ++i)
		{
			if (ImGui::Button(maps[i]->GetName().c_str()))
				selectedMap = maps[i];
		}
		ImGui::TreePop();
	}
}

void MapEditor::RenderRoomSelection()
{
	if (selectedMap && ImGui::TreeNode("Select Room"))
	{
		for (int i = 0; i < selectedMap->GetRooms().size(); ++i)
		{
			string buttonName = "Room " + to_string(i + 1);
			if (ImGui::Button(buttonName.c_str()))
				selectedRoom = selectedMap->GetRoom(i);
		}
		ImGui::TreePop();
	}
}

void MapEditor::RenderTileSelection()
{
	if (!selectedRoom) return;
	if (ImGui::TreeNode("Select Tile"))
	{
		for (int i = 0; i < tileSprites.size(); i++)
		{

		}
		ImGui::TreePop();
	}
}

void MapEditor::PlaceTile(int x, int y)
{
	if (!selectedRoom || selectedTileIndex < 0 || selectedTileIndex >= tileSprites.size())
		return;
}
