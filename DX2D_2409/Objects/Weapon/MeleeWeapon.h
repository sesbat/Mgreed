#pragma once

class MeleeWeapon : public Weapon
{
public:
    MeleeWeapon(wstring defaultImage);
    virtual ~MeleeWeapon();

    virtual void Update() override;
    virtual void Render() override;
    virtual void Attack() override;
    void ActiveCollider();
    void DeactivateCollider();
    BoxCollider* GetAttackCollider() { return attackCollider; }
protected:
    BoxCollider* attackCollider = nullptr;

    // Weapon을(를) 통해 상속됨
    
};