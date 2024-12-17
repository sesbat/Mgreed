#pragma once

class Boss;
class Robot : public RigidbodyObject
{
private:
    enum RobotActionState
    {
        IDLE, RUN, MELEE, SHOOT, JUMP , DIE,
    };

public:
    Robot();
    ~Robot();

    void Update();
    void Render();

    void Land();
    void EndAttack();
    void EndDie();
    void Damage();

    void SetBoss(Boss* boss) { this->boss = boss; }

    void CollisionCheck();

    bool IsRight() { return rot.y == 0.0f; }
private:    
    void Move();
    void Attack();
    void Jump();
    void SetDirection();
   
    //void Animation();
    
    void SetActionState(RobotActionState state);

    void CreateActions();

private:    
    RobotActionState curState = IDLE;
    map<RobotActionState, Action*> actions;

    int hp = 5;
    Slider* hpBar;

    Boss* boss;
};