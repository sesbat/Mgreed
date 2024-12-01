#pragma once

class ShootingScene : public Scene
{
private:
    const int INTERVAL = 100;

public:
    ShootingScene();
    ~ShootingScene();

    void Update() override;
    void Render() override;
    void PostRender() override;

private:
    void RandomFire();

private:
    Player* player;

    float time;    
};