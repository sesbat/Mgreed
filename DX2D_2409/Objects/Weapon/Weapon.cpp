#include "Framework.h"

Weapon::Weapon(wstring defaultImage)
{
	weaponImage = new Quad(defaultImage);
	weaponImage->SetParent(this);
	action = new Action();
}

Weapon:: ~Weapon()
{
	delete weaponImage;
	delete action;
}

void Weapon::Update()
{
	action->Update();
	weaponImage->UpdateWorld();
	UpdateWorld();
}

void Weapon::Render()
{
	if (isAttacking)
		action->Render();
	weaponImage->Render();
	GameObject::Render();
}
