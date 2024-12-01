#include "Framework.h"

RobotRun::RobotRun(Robot* robot)
    : RobotMove(robot)
{
    LoadClip("Textures/Robot/", "Robot_Run.xml", true);
}

RobotRun::~RobotRun()
{
}