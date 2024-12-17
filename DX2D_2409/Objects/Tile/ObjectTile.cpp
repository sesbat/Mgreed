#include "Framework.h"

ObjectTile::ObjectTile(wstring pilePath)
	:Tile(pilePath)
{
	type = OBJECT;
}

ObjectTile::~ObjectTile()
{
}
