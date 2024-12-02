#include "Framework.h"

RobotDead::RobotDead(Robot* robot)
	:RobotAction(robot)
{
	LoadClip("Textures/Robot/", "Robot_Dead.xml", false);
	clips[0]->SetEvent(bind(&Robot::EndDie, robot));
}

void RobotDead::Update()
{
	Action::Update();
}

void RobotDead::Render()
{
	Action::Render();
}
