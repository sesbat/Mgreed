#include "Framework.h"

DropObject::DropObject()
{
	action = new Action();
}

DropObject::~DropObject()
{
	delete action;
}

void DropObject::Update()
{
    RigidbodyObject::Update();
    CheckCollisionTiles();
	action->Update();
}

void DropObject::Render()
{
    RigidbodyObject::Render();
	action->Render();
}

void DropObject::CheckCollisionTiles()
{
	auto tiles = MapManager::Get()->GetSelectedMap()->GetCurrentRoom()->GetCollisionTiles();

    Vector2 tileSize = { 16,16 };
    int gridX = static_cast<int>(pos.x / tileSize.x);
    int gridY = static_cast<int>(pos.y / tileSize.y);

    int minY = max(0, gridY - 2);
    int maxY = min(static_cast<int>(tiles.size()) - 1, gridY + 2);

    int minX = max(0, gridX - 2);
    int maxX = min(static_cast<int>(tiles[0].size()) - 1, gridX + 2);

    Vector2 overlap = {};

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            Tile* tile = tiles[y][x];

            if (tile && IsCollision(tile, &overlap))
            {
                if (overlap.x > overlap.y)
                {
                    if (globalPos.y > tile->GetGlobalPos().y)
                    {
                        Translate(Vector2::Up() * overlap.y);
                        velocity.y = 0;
                        pos.y = tile->Top() + HalfSize().y;
                    }
                    else if (globalPos.y < tile->GetGlobalPos().y)
                    {
                        Translate(Vector2::Down() * overlap.y);
                        pos.y = tile->Bottom() - HalfSize().y;
                        velocity.y = 0;
                    }
                }
                else
                {
                    if (globalPos.x > tile->GetGlobalPos().x)
                    {
                        Translate(Vector2::Right() * overlap.x);
                        pos.x = tile->Right() + HalfSize().x;
                        if (velocity.x < 0)
                            velocity.x = 0;
                    }
                    else if (globalPos.x < tile->GetGlobalPos().x)
                    {
                        Translate(Vector2::Left() * overlap.x);
                        pos.x = tile->Left() - HalfSize().x;
                        if (velocity.x > 0)
                            velocity.x = 0;
                    }
                }
                break;
            }
        }
    }
}
