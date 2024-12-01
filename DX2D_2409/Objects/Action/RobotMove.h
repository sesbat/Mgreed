#pragma once

class RobotMove : public RobotAction
{
public:
    RobotMove(Robot* robot);

    void Update() override;
};