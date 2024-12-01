#pragma once

class TutorialScene : public Scene
{
private:
    const int SPAWN_INTERVAL = 200;
    const int POOL_SIZE = 100;

public:
    TutorialScene();
    ~TutorialScene();

    void Update() override;
    void Render() override;

private:
    void Spawn();

private:
    vector<Rect*> rects;

    int count = 0;
    int spawnNum = 0;

    // Scene을(를) 통해 상속됨
    void PostRender() override;
};