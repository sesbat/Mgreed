#include "Framework.h"

RobotShoot::RobotShoot(Robot* robot) : RobotAction(robot)
{
    LoadClip("Textures/Robot/", "Robot_Shoot.xml", false);

    clips[0]->SetEvent(bind(&Robot::EndAttack, robot));

    EffectManager::Get()->Add("Muzzle", 1, L"Textures/Effect/Muzzle.png", Vector2(4, 1), 1.0f, true);
}

void RobotShoot::Start()
{
    Action::Start();

    Fire();
}

void RobotShoot::Fire()
{
    Vector2 pos = robot->GetPos() + robot->GetRight() * 80;
    EffectManager::Get()->Play("Muzzle", pos);

    BulletManager::Get()->Fire(pos, robot->GetRight(), "Robot");
}
