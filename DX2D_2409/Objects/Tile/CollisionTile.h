#pragma once

class CollisionTile : public ImageObject
{
public:
	CollisionTile(wstring textureFile, float maxFrameX = 1, float maxFrameY = 1);
	~CollisionTile();

	void Update();
	void Render();
private:
};

