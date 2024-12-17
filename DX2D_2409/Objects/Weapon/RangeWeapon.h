#pragma once

class RangeWeapon : public Weapon
{
public:
	RangeWeapon(wstring defaultImage, Vector2 colliderSize);
	~RangeWeapon();

	void Update();
	void Render();

private:
};
