#pragma once

class Action
{
public:
    Action() = default;
    Action(string path, string file, bool isLoop, float speed = 1.0f);
    virtual ~Action();

    virtual void Update();
    virtual void Render();

    virtual void Start();
    virtual void End() {}

    void SetEvent(string key, Event event) { events[key] = event; }

    Clip* GetClip(int index) { return clips[index]; }
    Clip* GetCurClip() { return clips[curState]; }

    void LoadClip(string path, string file, bool isLoop, float speed = 1.0f);
    void LoadClip(wstring file, int frameX, int frameY, bool isLoop, float speed = 1.0f);

    void SetState(int state);

protected:
    vector<Clip*> clips;
    int curState = 0;

    map<string, Event> events;
};