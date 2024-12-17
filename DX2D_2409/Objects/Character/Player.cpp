#include "Framework.h"
#include "Player.h"

Player::Player()
{
	hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
		L"Textures/UI/HealthBarBack.png");
	hpBar->SetPos(CENTER_X, SCREEN_HEIGHT - 100);
	hpBar->SetParent(this);
    UpdateSize({ 17,21 });
	pos = CENTER;
	CreateActions();

    handle = new BoxCollider({ 10,10 });
    handle->SetParent(this);
    handle->SetPos({ 30,0 });
    currentWeapon = new GreatSword();
    currentWeapon->SetParent(handle);
    currentWeapon->SetPos({ 0,0 });
}

Player::~Player()
{
	delete hpBar;
    delete handle;
    delete currentWeapon;
}

void Player::Update()
{
	Move();
	Jump();
    Dash();
    hpBar->UpdateWorld();
	RigidbodyObject::Update();

    SetDirection();
	actions[curState]->Update();

    CursorFollow();
    handle->UpdateWorld();
    currentWeapon->Update();
    Attack();
}

void Player::Render()
{
	hpBar->Render();
	RigidbodyObject::Render();
	actions[curState]->Render();

    handle->Render();
    currentWeapon->Render();
}

void Player::Move()
{
	if (curState >= JUMP) return;

	bool isMove = false;

	isMove |= KEY->Press('D');
	isMove |= KEY->Press('A');

	isMove ? SetActionState(RUN) : SetActionState(IDLE);
}

void Player::Jump()
{
	if (curState >= JUMP) return;

    isGround = false;
	if (KEY->Down('W') || KEY->Down(VK_SPACE))
		SetActionState(JUMP);
}

void Player::Attack()
{
    if (currentWeapon)
    {
        if (KEY->Down(VK_LBUTTON))
            currentWeapon->Attack();
        currentWeapon->Update();
    }
}

void Player::Dash()
{
    coolDownTimer += DELTA;
    if (coolDownTimer >= DASH_COOL_DOWN)
    {
        coolDownTimer -= DASH_COOL_DOWN;

        if (dashCount > 0)
            dashCount--;
    }
    if (dashCount == MAX_DASH_COUNT)
        return;

    if (KEY->Down(VK_RBUTTON))
    {
        SetActionState(DASH);
        dashCount++;
    }
}

void Player::Land()
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

void Player::SetDirection()
{
    if (worldMousePos.x > pos.x)
    {
        rot.y = 0.0f;
    }
    else
    {
        rot.y = PI;
    }
}

void Player::CursorFollow()
{
    Vector2 handlePos = handle->GetGlobalPos();
    Vector2 direction = (worldMousePos - handlePos).Normalized();

    float angle = atan2(direction.y, direction.x);
    if (rot.y == 0.0f)
        handle->SetRotZ(atan2(direction.y, direction.x));
    else
        handle->SetRotZ(PI - atan2(direction.y, direction.x));
}

void Player::CheckCollisionTiles(const vector<vector<Tile*>>& tiles)
{
    Vector2 tileSize = { 16,16 };
    int gridX = static_cast<int>(pos.x / tileSize.x);
    int gridY = static_cast<int>(pos.y / tileSize.y);

    int minY = max(0, gridY - 2);
    int maxY = min(static_cast<int>(tiles.size()) - 1, gridY + 2);

    int minX = max(0, gridX - 2);
    int maxX = min(static_cast<int>(tiles[0].size()) - 1, gridX + 2);

    Vector2 overlap = {};

    for (int y = minY; y <= maxY; ++y)
    {
        for (int x = minX; x <= maxX; ++x)
        {
            Tile* tile = tiles[y][x];

            if (tile && IsCollision(tile, &overlap))
            {
                if (overlap.x > overlap.y)
                {
                    if (globalPos.y > tile->GetGlobalPos().y)
                    {
                        Translate(Vector2::Up() * overlap.y);
                        velocity.y = 0;
                        isGround = true;
                        pos.y = tile->Top() + HalfSize().y;
                    }
                    else if (globalPos.y < tile->GetGlobalPos().y)
                    {
                        Translate(Vector2::Down() * overlap.y);
                        pos.y = tile->Bottom() - HalfSize().y;
                        velocity.y = 0;
                    }
                }
                else
                {
                    if (globalPos.x > tile->GetGlobalPos().x)
                    {
                        Translate(Vector2::Right() * overlap.x);
                        pos.x = tile->Right() + HalfSize().x;
                        if (velocity.x < 0)
                            velocity.x = 0;
                    }
                    else if (globalPos.x < tile->GetGlobalPos().x)
                    {
                        Translate(Vector2::Left() * overlap.x);
                        pos.x = tile->Left() - HalfSize().x;
                        if (velocity.x > 0)
                            velocity.x = 0;
                    }
                }
            }
        }
    }
}

void Player::CreateActions()
{
	actions[IDLE] = new Action("Textures/Dungreed/Character/Idle/", "Idle.xml", true, 1.0f);
	actions[RUN] = new PlayerRun(this);
	actions[JUMP] = new PlayerJump(this);
    actions[DASH] = new PlayerDash(this);
}
