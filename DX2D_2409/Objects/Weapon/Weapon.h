#pragma once

class Weapon : public GameObject
{
public:
    Weapon(wstring defaultImage);
    virtual ~Weapon();

    virtual void Update();
    virtual void Render();
    virtual void Attack() = 0; 

    void SetAction(Action* action) { this->action = action; }

protected:
    Quad* weaponImage = nullptr;
    Action* action = nullptr; 
    bool isAttacking = false;
};
