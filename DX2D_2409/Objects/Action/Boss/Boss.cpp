#include "Framework.h"

Boss::Boss()
{
	UpdateSize(Vector2(150, 230));
	pos = CENTER;

	hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
		L"Textures/UI/HealthBarBack.png");
	hpBar->SetParent(this);
	hpBar->SetPos(0, 150);

	CreateActions();
}

Boss::Boss(Robot* robot)
{
	this->robot = robot;
	UpdateSize(Vector2(150, 230));
	pos = CENTER;

	hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
		L"Textures/UI/HealthBarBack.png");
	hpBar->SetParent(this);
	hpBar->SetPos(0, 150);

	CreateActions();
}

Boss::~Boss()
{
	for (pair<ActionState, Action*> action : actions)
		delete action.second;
	delete hpBar;
}

void Boss::Update()
{
	RigidbodyObject::Update();

	intervalTime += DELTA;

	if (hp > 0 && intervalTime >= attackDelay)
	{
		SetActionState(LASER);
		intervalTime = 0.0f;
	}
	Move();
	Gravity();
	CollisionCheck();
	actions[curState]->Update();
	hpBar->UpdateWorld();
}

void Boss::Render()
{
	if (!isActive)return;

	BoxCollider::Render();
	actions[curState]->Render();
	hpBar->Render();
}

void Boss::CollisionCheck()
{
	BossLaser* laser = dynamic_cast<BossLaser*>(actions[LASER]);
	if (robot->IsCollision(laser->GetAttackCollider()))
	{
		robot->Damage();
		laser->GetAttackCollider()->SetActive(false);
	}
}

void Boss::SetDirection()
{
	if (velocity.x < 0.0f)
		rot.y = 0.0f;
	else if (velocity.x > 0.0f)
		rot.y = PI;
}

void Boss::SetActionState(ActionState state)
{
	if (curState == state)
		return;

	curState = state;
	actions[curState]->Start();
}

void Boss::EndAttack()
{
	SetActionState(IDLE);
}

void Boss::EndMove()
{
	SetActionState(IDLE);
}

void Boss::EndDie()
{
	SetActive(false);
}

void Boss::Move()
{
	if (curState == LASER || curState == DIE) return;

	Vector2 dir = (robot->GetPos() - pos).Normalized();

	if (dir.x > 0)
		HorizontalMove(true);
	else
		HorizontalMove(false);
	SetDirection();
}

void Boss::Gravity()
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

void Boss::Damage()
{
	hp--;

	hpBar->SetAmount(hp / 5.0f);

	if (hp == 0)
	{
		SetActionState(DIE);
	}
}

void Boss::CreateActions()
{
	actions[IDLE] = new Action(L"Textures/Mgreed/BossIdle.png", 8, 1, true);
	actions[LASER] = new BossLaser(this, robot);
	actions[DIE] = new BossDie(this);
	actions[MOVE] = new BossMove(this);
}
