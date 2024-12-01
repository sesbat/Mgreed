#include "Framework.h"

RobotMove::RobotMove(Robot* robot) : RobotAction(robot)
{
}

void RobotMove::Update()
{
    if (KEY->Press('A'))
        robot->HorizontalMove(false);
    if (KEY->Press('D'))
        robot->HorizontalMove(true);

    Action::Update();
}
