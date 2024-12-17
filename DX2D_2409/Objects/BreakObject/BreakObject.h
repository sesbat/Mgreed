#pragma once

class BreakObject : public GameObject
{
public:
    BreakObject(wstring defaultImage);
    virtual ~BreakObject();

    virtual void Update();
    virtual void Render();
    virtual void Break() = 0;

    void SetAction(Action* action) { this->action = action; }

protected:
    Quad* objectImage = nullptr;
    Action* action = nullptr;

};
