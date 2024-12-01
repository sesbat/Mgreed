#pragma once

class RobotJump : public RobotMove
{
private:
    const float JUMP_POWER = 500.0f;
    const UINT MAX_JUMP_COUNT = 2;

    enum JumpState
    {
        START, LOOP, END
    };

public:
    RobotJump(Robot* robot);

    void Update() override;

    void Start() override;

private:
    void Loop();
    void EndJumpStart();

private:
    int jumpCount = 0;
};