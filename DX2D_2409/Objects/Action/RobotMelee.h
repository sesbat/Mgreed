#pragma once

class RobotMelee : public RobotAction
{
public:
    RobotMelee(Robot* robot);
    ~RobotMelee();

    void Update() override;
    void Render() override;

private:
    void OnActiveCollider();
    void OnInactiveCollider();

private:
    BoxCollider* attackCollider;
};