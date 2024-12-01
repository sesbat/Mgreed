#include "Framework.h"

Player::Player() : Quad(L"Textures/airplane.png")
{
    pos = { CENTER_X, CENTER_Y };    

    firePos = new Poly(3, 30);    
    firePos->SetParent(this);
    firePos->SetPos(50, 0);

    collider = new CircleCollider(size.x * 0.5f);
    collider->SetParent(this);

    hpBar = new Slider(L"Textures/UI/HealthBarFront.png",
        L"Textures/UI/HealthBarBack.png");

    //hpBar->SetParent(this);
    hpBar->SetPos(CENTER_X, SCREEN_HEIGHT - 100);
}

Player::~Player()
{
    delete firePos;
    delete collider;
    delete hpBar;
}

void Player::Update()
{
    Move();
    Rotate();
    Fire();        

    UpdateWorld();
    firePos->UpdateWorld();
    collider->UpdateWorld();

    hpBar->UpdateWorld();
}

void Player::Render()
{
    Quad::Render();
    firePos->Render();
    collider->Render();    
}

void Player::PostRender()
{
    ImGui::Text("Hp : %d\n", hp);
    hpBar->Render();
}

void Player::Damage()
{
    hp--;

    hpBar->SetAmount(hp / 100.0f);
}

void Player::Move()
{
    if (KEY->Press('W'))
    {
        //pos += Vector2::Up() * moveSpeed;
        //pos.x += cos(rot.z) * moveSpeed;
        //pos.y += sin(rot.z) * moveSpeed;
        pos += GetRight() * moveSpeed * DELTA;
    }
    if (GetAsyncKeyState('S'))
    {
        pos -= GetRight() * moveSpeed * DELTA;
    }
    if (GetAsyncKeyState('A'))
    {
        rot.z += rotSpeed * DELTA;
    }
    if (GetAsyncKeyState('D'))
    {
        rot.z -= rotSpeed * DELTA;
    }
}

void Player::Rotate()
{
    //firePos->SetPos(pos + GetRight() * distance);

    Vector2 dir = mousePos - firePos->GetGlobalPos();
    
    firePos->SetRot(0, 0, atan2(dir.y, dir.x) - rot.z);
}

void Player::Fire()
{
    if (KEY->Down(VK_LBUTTON))
    {
        Vector2 dir = mousePos - firePos->GetGlobalPos();
        BulletManager::Get()->Fire(firePos->GetGlobalPos(), dir, "Player", Float4(1, 0, 0, 1));
    }
}
