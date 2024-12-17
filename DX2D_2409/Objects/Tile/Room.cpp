#include "Framework.h"
#include "Room.h"

Room::Room(int width, int height, Quad* backGround)
	: width(width), height(height), backGround(backGround)
{
	editTiles.resize(height, vector<EditTile*>(width, nullptr));
	tiles.resize(height, vector<Tile*>(width, nullptr));

	CreateTiles();
	EventManager::Get()->AddEvent("UpdateInstance", bind(&Room::UpdateInstanceData, this));
	if (backGround)
	{
		backGround->SetPos(CENTER);
		backGround->UpdateWorld();
	}
}

Room::Room()
	:width(10), height(10), backGround(nullptr)
{
	editTiles.resize(height, vector<EditTile*>(width, nullptr));
	tiles.resize(height, vector<Tile*>(width, nullptr));
	CreateTiles();
}

Room::~Room()
{
	delete backGround;
	backGround = nullptr;
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (editTiles[y][x])
				delete editTiles[y][x];
			if (tiles[y][x])
				delete tiles[y][x];
		}
	}
}

void Room::Update()
{
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (editTiles[y][x])
				editTiles[y][x]->Update();
			if (tiles[y][x])
				tiles[y][x]->Update();
		}
	}
	PLAYER->CheckCollisionTiles(tiles);
}

void Room::Render()
{
	if (backGround)
		backGround->Render();

	instanceBuffer->Set(1);

	quad->GetMaterial()->Set();
	quad->GetMesh()->SetMesh();

	deviceContext->DrawIndexedInstanced(6, width * height + 50, 0, 0, 0);

	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			if (editTiles[y][x])
				editTiles[y][x]->Render();
			if (tiles[y][x])
				tiles[y][x]->Render();
		}
	}
}

void Room::SetEditTile(int x, int y, Vector2 frame)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	if (!editTiles[y][x])
		return;

	editTiles[y][x]->SetInstanceData(frame);
	UpdateInstanceData();
}

void Room::SetObjectTile(Quad* tile, int x, int y)
{
}

void Room::SetCollisionTile(int x, int y, wstring file)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	if (tiles[y][x])
	{
		if (tiles[y][x]->GetImage()->GetMaterial()->GetTexture()->GetFile() == file)
			return;

		delete tiles[y][x];
		tiles[y][x] = nullptr;
	}
	tiles[y][x] = new Tile(file);
	tiles[y][x]->SetPos(tileSize * Vector2(x, y));
	tiles[y][x]->SetParent(this);
	//collisionTiles[y][x]->UpdateWorld();
	tiles[y][x]->Update();
}

void Room::AddTile(Tile* tile, int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;

	if (tiles[y][x])
		delete tiles[y][x];

	tiles[y][x] = tile;
	tiles[y][x]->SetParent(this);
	tiles[y][x]->SetPos(Vector2(x * tile->Size().x, y * tile->Size().y));
	tiles[y][x]->Update();
}

void Room::RemoveTile(int x, int y)
{
	if (x < 0 || x >= width || y < 0 || y >= height)
		return;
	if (!tiles[y][x])
		return;

	delete tiles[y][x];
	tiles[y][x] = nullptr;
}

void Room::Save(BinaryWriter& writer)
{
	writer.UInt(width);
	writer.UInt(height);

	writer.WString(backGround->GetMaterial()->GetTexture()->GetFile());
	// Save Edit Tiles
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Vector2 frame = editTiles[y][x] ? editTiles[y][x]->GetInstanceData()->curFrame : Vector2(-1, -1);
			writer.Vector(frame);
		}
	}

	// Save Collision Tiles
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			wstring file = tiles[y][x] ? tiles[y][x]->GetImage()->GetMaterial()->GetTexture()->GetFile() : L"";
			writer.WString(file);
		}
	}
}

void Room::Load(BinaryReader& reader)
{
	/* width = reader.UInt();
	 height = reader.UInt();*/

	 // Resize the vectors
	editTiles.resize(height, vector<EditTile*>(width, nullptr));
	tiles.resize(height, vector<Tile*>(width, nullptr));

	// Load Edit Tiles
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			Vector2 frame = reader.Vector();
			if (frame.x >= 0 && frame.y >= 0)
			{
				editTiles[y][x]->SetInstanceData(frame);
			}
		}
	}
	UpdateInstanceData();

	// Load Collision Tiles
	for (int y = 0; y < height; ++y)
	{
		for (int x = 0; x < width; ++x)
		{
			wstring file = reader.WString();
			if (!file.empty())
			{
				tiles[y][x] = new Tile(file);
				tiles[y][x]->SetPos(tileSize * Vector2(x, y));
				tiles[y][x]->SetParent(this);
				tiles[y][x]->Update();
				//tiles[y][x]->UpdateWorld();
			}
		}
	}
}

void Room::CreateTiles()
{
	Vector2 maxFrame = { 38, 1 };

	quad = new Quad(L"Textures/Dungreed/Tiles/BackGroundTiles.png", Vector2(),
		Vector2(1 / maxFrame));
	quad->GetMaterial()->SetShader(L"Shaders/Instancing.hlsl");

	tileSize = quad->GetSize();

	UINT size = width * height;
	backGroundObjectInstances.resize(30);
	instances.resize(size);
	editTiles.reserve(size);
	tiles.reserve(size);
	for (int y = 0; y < height; y++)
	{
		for (int x = 0; x < width; x++)
		{
			int index = y * width + x;

			EditTile* editTile = new EditTile(tileSize, &instances[index]);
			editTile->SetPos(tileSize * Vector2(x, y));
			editTile->SetParent(this);
			editTile->UpdateWorld();
			instances[index].transform = XMMatrixTranspose(editTile->GetWorld());
			instances[index].curFrame = { 0 , 0 };
			instances[index].maxFrame = maxFrame;

			editTiles[y][x] = editTile;
			tiles[y][x] = nullptr;
		}
	}

	instanceBuffer = new VertexBuffer(instances.data(), sizeof(InstanceData), size);
}

void Room::UpdateInstanceData()
{
	instanceBuffer->Update(instances.data(), instances.size());
}
