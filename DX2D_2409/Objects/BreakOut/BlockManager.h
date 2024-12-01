#pragma once

class BlockManager : public Singleton<BlockManager>
{
public:
    BlockManager();
    ~BlockManager();

    void Render();

    void LoadStage(int stageNum);

    void CollisionBall(Ball* ball);

    void SetStartPos(Vector2 pos) { startPos = pos; }

    bool CheckClear();

private:
    void NextStage();
    void DeleteBlocks();

private:
    vector<Block*> blocks;
    Vector2 startPos;
    int stage = 0;
};