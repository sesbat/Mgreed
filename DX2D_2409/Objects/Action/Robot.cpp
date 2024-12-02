#include "Framework.h"

Robot::Robot()
{
    UpdateSize(Vector2(150, 230));
    pos = CENTER;

    hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
        L"Textures/UI/HealthBarBack.png");
    hpBar->SetParent(this);
    hpBar->SetPos(0, 150);

    CreateActions();
    //SetActionState(JUMP);
}

Robot::~Robot()
{
    for (pair<ActionState, Action*> action : actions)
        delete action.second;
    delete hpBar;
}

void Robot::Update()
{
    RigidbodyObject::Update();

    Move();
    Attack();    
    Jump();
    SetDirection();
    Gravity();
    CollisionCheck();
   hpBar->UpdateWorld();

    actions[curState]->Update();
}

void Robot::Render()
{
    if (!isActive) return;

    BoxCollider::Render();
    actions[curState]->Render();
    hpBar->Render();
}

void Robot::Land()
{
    SetActionState(IDLE);
}

void Robot::Move()
{
    if (curState >= MELEE) return;

    bool isMove = false;

    isMove |= KEY->Press('D');
    isMove |= KEY->Press('A');

    isMove ? SetActionState(RUN) : SetActionState(IDLE);   
}

void Robot::Attack()
{
    if (curState == MELEE || curState == SHOOT) return;

    if (KEY->Down(VK_LBUTTON))
    {
        SetActionState(MELEE);
    }

    if (KEY->Down(VK_RBUTTON))
    {
        SetActionState(SHOOT);
    }
}

void Robot::Jump()
{
    if (curState >= MELEE) return;

    if (KEY->Down('W'))
    {
        SetActionState(JUMP);
    }
}

void Robot::SetDirection()
{
    if (velocity.x > 0.0f)
        rot.y = 0.0f;
    else if (velocity.x < 0.0f)
        rot.y = PI;
}

void Robot::Damage()
{
    hp--;

    hpBar->SetAmount(hp / 5.0f);
    if (hp == 0)
        SetActionState(DIE);
}

void Robot::CollisionCheck()
{
    if (boss == nullptr) return;
    RobotMelee* melee = dynamic_cast<RobotMelee*>(actions[MELEE]);
    if (boss->IsCollision(melee->GetAttackCollider()))
    {
        boss->Damage();
        melee->GetAttackCollider()->SetActive(false);
    }
}

//void Robot::Animation()
//{
//    if (curState == ATTACK) return;
//
//    if (velocity.x > 0.0f)
//        rot.y = 0.0f;
//    else if (velocity.x < 0.0f)
//        rot.y = PI;
//
//    if (abs(velocity.x) > 10.0f)
//        SetActionState(RUN);
//    else
//        SetActionState(IDLE);
//}

void Robot::SetActionState(ActionState state)
{
    if (curState == state)
        return;

    curState = state;
    actions[curState]->Start();
}

void Robot::EndAttack()
{
    SetActionState(IDLE);
}

void Robot::EndDie()
{
    SetActive(false);
}

void Robot::Gravity()
{
    RigidbodyObject::Gravity();
    if (Bottom() < 0.0f)
    {
        SetVelocityY(0.0f);
        Vector2 pos = GetPos();
        pos.y = HalfSize().y;
        SetPos(pos);
    }
}

void Robot::CreateActions()
{
    actions[IDLE] = new Action("Textures/Robot/", "Robot_Idle.xml", true);
    actions[RUN] = new RobotRun(this);
    actions[JUMP] = new RobotJump(this);
    actions[MELEE] = new RobotMelee(this);
    actions[SHOOT] = new RobotShoot(this);
    actions[DIE] = new RobotDead(this);
}
