#include "Framework.h"

RobotJump::RobotJump(Robot* robot) : RobotMove(robot)
{
    LoadClip("Textures/Robot/", "Robot_JumpUp.xml", false);
    LoadClip("Textures/Robot/", "Robot_Jumping.xml", true);
    LoadClip("Textures/Robot/", "Robot_JumpDown.xml", false);

    clips[START]->SetEvent(bind(&RobotJump::EndJumpStart, this));
    clips[END]->SetEvent(bind(&Robot::Land, robot));
}

void RobotJump::Update()
{
    Loop();

    if(curState != END)
        robot->Gravity();

    if (curState != START && jumpCount < MAX_JUMP_COUNT && KEY->Down('W'))
    {
        SetState(START);
        robot->SetVelocityY(JUMP_POWER);
        jumpCount++;
    }

    RobotMove::Update();
}

void RobotJump::Start()
{
    curState = START;
    clips[curState]->Play();
    robot->SetVelocityY(JUMP_POWER);
    jumpCount = 1;
}

void RobotJump::Loop()
{
    if (curState != LOOP) return;

    if (robot->Bottom() < 0.0f)
    {
        robot->SetVelocityY(0.0f);
        Vector2 pos = robot->GetPos();
        pos.y = robot->HalfSize().y;
        robot->SetPos(pos);

        SetState(END);
    }
}

void RobotJump::EndJumpStart()
{
    SetState(LOOP);
}
