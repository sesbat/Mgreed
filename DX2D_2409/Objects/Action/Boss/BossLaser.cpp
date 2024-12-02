#include "Framework.h"

BossLaser::BossLaser(Boss* boss, Robot* robot)
	: BossAction(boss),robot(robot)
{
    attackCollider = new BoxCollider({ 500, 200 });
    attackCollider->SetParent(boss);
    attackCollider->SetActive(false);

    EffectManager::Get()->Add("Laser", 10, L"Textures/Mgreed/Laser.png", Vector2(39, 1));

    LoadClip(L"Textures/Mgreed/BossAttack.png", 29, 1, false);
    clips[0]->SetEvent(bind(&Boss::EndAttack, boss));
    clips[0]->SetEvent(bind(&BossLaser::OnActiveCollider, this), 22);
    clips[0]->SetEvent(bind(&BossLaser::OnInactiveCollider, this), 27);
}

void BossLaser::OnActiveCollider()
{
    attackCollider->SetActive(true);
}

void BossLaser::OnInactiveCollider()
{
    attackCollider->SetActive(false);
}

void BossLaser::Update()
{
    attackCollider->UpdateWorld();
    for (int i = 0; i < 3; i++)
    {
        EffectManager::Get()->Play("Laser", { boss->GetPos().x + (i - 1) * 200,boss->GetPos().y - 100});
    }
    if (attackCollider->IsCollision(robot))
    {
        robot->Damage();
        attackCollider->SetActive(false);
    }
    Action::Update();
}

void BossLaser::Render()
{
    Action::Render();
    attackCollider->Render();
}
