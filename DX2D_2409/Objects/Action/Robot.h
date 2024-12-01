#pragma once

class Robot : public RigidbodyObject
{
private:
    enum ActionState
    {
        IDLE, RUN, MELEE, SHOOT, JUMP
    };

public:
    Robot();
    ~Robot();

    void Update();
    void Render();

    void Land();
    void EndAttack();

    bool IsRight() { return rot.y == 0.0f; }
private:    
    void Move();
    void Attack();
    void Jump();
    void SetDirection();
    //void Animation();
    
    void SetActionState(ActionState state);    

    void CreateActions();

private:    
    ActionState curState = IDLE;
    map<ActionState, Action*> actions;
};