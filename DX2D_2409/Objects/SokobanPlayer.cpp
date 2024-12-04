#include "Framework.h"

SokobanPlayer::SokobanPlayer()
{
	tag = "SokobanPlayer";
	player = new Quad(L"Textures/Tile/SokobanPack/PNG/Defaultsize/Player/player_01.png");
	player->SetParent(this);
	pos = CENTER;
}

SokobanPlayer::~SokobanPlayer()
{
	delete player;
}

void SokobanPlayer::Update()
{
	Move();
	player->UpdateWorld();
	BoxCollider::UpdateWorld();
}

void SokobanPlayer::Render()
{
	BoxCollider::Render();
	player->Render();
}

void SokobanPlayer::Move()
{
	if (KEY->Press(VK_RIGHT))
		Translate(Vector2::Right() * speed * DELTA);
	if (KEY->Press(VK_LEFT))
		Translate(Vector2::Left() * speed * DELTA);
	if (KEY->Press(VK_UP))
		Translate(Vector2::Up() * speed * DELTA);
	if (KEY->Press(VK_DOWN))
		Translate(Vector2::Down() * speed * DELTA);
}
