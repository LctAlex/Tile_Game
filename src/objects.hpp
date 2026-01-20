#pragma once
#include "raylib.h"

class Solid //base class
{
    protected:
    Rectangle rec;
    public:
    Solid(Rectangle rec);

    Rectangle GetRec();
    
    void Draw(Color color);

    virtual void Update();
    virtual ~Solid();
};

class Trap: public Solid
{
    private:
    Vector2 spike[3];
    public:
    bool rising; //yeah we'll just make ts public cuz I need access
    Trap(Rectangle rec);
    Vector2 GetSpike(int index);
    void SetToRise();
    void RiseSpike();
    void Update() override;
};

class Slime: public Solid
{
    public:
    Slime(Rectangle rec);
    void Update() override;
};