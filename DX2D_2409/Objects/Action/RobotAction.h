#pragma once

class RobotAction : public Action
{
public:
    RobotAction(Robot* robot);

protected:
    Robot* robot;
};