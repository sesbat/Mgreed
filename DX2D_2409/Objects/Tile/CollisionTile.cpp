#include "Framework.h"

CollisionTile::CollisionTile(wstring pilePath)
	:Tile(pilePath)
{
	type = COLLISION;
}

CollisionTile::~CollisionTile()
{
}
