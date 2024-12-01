#pragma once

class Block : public ImageObject
{
public:
    Block(int type);
    ~Block();

    void Render();

    void Damage();

    int GetHp() { return curHp; }

private:
    void SetFrame();

private:
    int type;
    int curHp;
};