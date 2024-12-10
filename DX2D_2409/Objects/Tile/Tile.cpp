#include "Framework.h"

Tile::Tile(wstring file, Vector2 startUV, Vector2 endUV)
	: ImageObject(file, startUV, endUV)
{
}

Tile::~Tile()
{
}
