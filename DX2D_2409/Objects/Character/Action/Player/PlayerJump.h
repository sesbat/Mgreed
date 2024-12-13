#pragma once

class PlayerJump : public PlayerMove
{
private:
    const float JUMP_POWER = 500.0f;

    enum JumpState
    {
        START, LOOP, END
    };

public:
    PlayerJump(Player* player);

    void Update() override;
    void Start() override;

private:
    void Loop();
    void EndJumpStart();
};