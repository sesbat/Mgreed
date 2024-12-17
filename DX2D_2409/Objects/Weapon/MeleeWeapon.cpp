#include "Framework.h"

MeleeWeapon::MeleeWeapon(wstring defaultImage)
    : Weapon(defaultImage)
{
}

MeleeWeapon::~MeleeWeapon()
{
    delete attackCollider;
}

void MeleeWeapon::Update()
{
    Weapon::Update();
    attackCollider->UpdateWorld();
}

void MeleeWeapon::Render()
{
    Weapon::Render();
    attackCollider->Render();
}

void MeleeWeapon::ActiveCollider()
{
    attackCollider->SetActive(true);
    weaponImage->SetActive(false);
    isAttacking = true;
}

void MeleeWeapon::DeactivateCollider()
{
    attackCollider->SetActive(false);
    weaponImage->SetActive(true);
    isAttacking = false;
}

void MeleeWeapon::Attack()
{
}
