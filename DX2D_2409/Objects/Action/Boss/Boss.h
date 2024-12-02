#pragma once

class Boss : public RigidbodyObject
{
private:
    enum ActionState
    {
        IDLE,MOVE, LASER , DIE
    };

public:
    Boss();
    Boss(Robot* robot);
    ~Boss();

    void Update();
    void Render();

    void CollisionCheck();

    void SetPlayer(Robot* robot) { this->robot = robot; }
    void SetDirection();
    void SetActionState(ActionState state);

    void EndAttack();
    void EndMove();
    void EndDie();

    void Move();
    void Gravity() override;
    void Damage();
    void CreateActions();
private:
    ActionState curState = IDLE;
    map<ActionState, Action*> actions;

    Robot* robot;

    float attackDelay = 5.0f;
    float intervalTime = 0.0f;
    Slider* hpBar;
    int hp = 5;
};

