#pragma once

class RobotShoot : public RobotAction
{
public:
    RobotShoot(Robot* robot);

    void Start() override;
private:
    void Fire();
};