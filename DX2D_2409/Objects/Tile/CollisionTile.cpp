#include "Framework.h"
#include "CollisionTile.h"

CollisionTile::CollisionTile(wstring textureFile, float maxFrameX, float maxFrameY)
	:ImageObject(textureFile, maxFrameX, maxFrameY)
{
}

CollisionTile::~CollisionTile()
{
}

void CollisionTile::Update()
{
	ImageObject::Update();
}

void CollisionTile::Render()
{
	ImageObject::Render();
}
