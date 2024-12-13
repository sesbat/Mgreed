#include "Framework.h"
#include "Player.h"

Player::Player()
{
	CreateActions();

	hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
		L"Textures/UI/HealthBarBack.png");

	hpBar->SetPos(CENTER_X, SCREEN_HEIGHT - 100);
	pos = CENTER;

}

Player::~Player()
{
	delete hpBar;
}

void Player::Update()
{
	Move();
	Jump();
	hpBar->UpdateWorld();
	RigidbodyObject::Update();
	actions[curState]->Update();
}

void Player::Render()
{
	hpBar->Render();
	RigidbodyObject::Render();
	actions[curState]->Render();
}

void Player::Move()
{
	if (curState >= JUMP) return;

	bool isMove = false;

	isMove |= KEY->Press('D');
	isMove |= KEY->Press('A');

	isMove ? SetActionState(MOVE) : SetActionState(IDLE);
}

void Player::Jump()
{
	if (curState >= JUMP) return;

	if (KEY->Down('W') || KEY->Down(VK_SPACE))
		SetActionState(JUMP);
}

void Player::Attack()
{
}

void Player::OnGround()
{
	SetActionState(IDLE);
}

void Player::SetActionState(ActionState state)
{
	if (curState == state)
		return;

	curState = state;
	actions[curState]->Start();
}

void Player::CreateActions()
{
	actions[IDLE] = new Action("Textures/Maple/DefaultCharacter/Stand/", "Stand.xml", true, 1.0f);
	actions[MOVE] = new PlayerMove(this);
	actions[JUMP] = new PlayerJump(this);
}
