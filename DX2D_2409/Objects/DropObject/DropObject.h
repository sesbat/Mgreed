#pragma once

class DropObject : public RigidbodyObject
{
public:
	DropObject();
	~DropObject();
	
	void Update();
	void Render();

	void CheckCollisionTiles();
protected:
	Action* action;
};
