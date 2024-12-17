#include "Framework.h"

GreatSword::GreatSword()
    : MeleeWeapon(L"Textures/Dungreed/Weapon/GreatSword/GreatSword.png") 
{
    weaponImage->SetPos({ 0, 10 });
    attackCollider = new BoxCollider({ 20 , 30 });
    attackCollider->SetParent(this);
    attackCollider->SetPos({ 20,10 });
    attackCollider->SetActive(false);

    action->LoadClip("Textures/Dungreed/Weapon/GreatSword/", "GreatSwordAttack.xml", false,1.0f,Vector2(0,10));
    action->GetClip(0)->SetEvent(bind(&MeleeWeapon::ActiveCollider, this), 1);
    action->GetClip(0)->SetEvent(bind(&MeleeWeapon::DeactivateCollider, this), 6);
}

GreatSword::~GreatSword()
{
}

void GreatSword::Attack()
{
    MeleeWeapon::Attack();
    action->GetClip(0)->Play();
}
