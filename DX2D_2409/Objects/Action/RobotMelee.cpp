#include "Framework.h"
#include "RobotMelee.h"

RobotMelee::RobotMelee(Robot* robot) : RobotAction(robot)
{
    attackCollider = new BoxCollider({ 150, 200 });
    attackCollider->SetParent(robot);
    attackCollider->SetPos(60, 0);
    attackCollider->SetActive(false);

    LoadClip("Textures/Robot/", "Robot_Melee.xml", false);
    clips[0]->SetEvent(bind(&Robot::EndAttack, robot));
    clips[0]->SetEvent(bind(&RobotMelee::OnActiveCollider, this), 2);
    clips[0]->SetEvent(bind(&RobotMelee::OnInactiveCollider, this), 5);
}

RobotMelee::~RobotMelee()
{
    delete attackCollider;
}

void RobotMelee::Update()
{
    attackCollider->UpdateWorld();

    Action::Update();
}

void RobotMelee::Render()
{
    Action::Render();

    attackCollider->Render();
}

void RobotMelee::OnActiveCollider()
{
    attackCollider->SetActive(true);
}

void RobotMelee::OnInactiveCollider()
{
    attackCollider->SetActive(false);
}