#pragma once
#include "raylib.h"
#include <iostream> //for debug

class Solid //base class
{
    protected:
    Rectangle rec;
    public:
    Solid(Rectangle rec);
    Rectangle GetRec();
    virtual void SetBool();
    virtual bool GetBool(); //GOOD IDEA!
    virtual void Update(); //different updates per class
    virtual void Draw(Color color = BLACK);
    virtual ~Solid();
};

class Trap: public Solid
{
    private:
    Vector2 spike[3];
    public:
    bool rising; //yeah we'll just make ts public cuz I need access
    Trap(Rectangle rec);
    Vector2 GetSpike(int index); //should make a virtual void GetVec2() in Solid
    void RiseSpike(); //SetVec2() in Solid
    void SetBool() override;
    void Update() override;
    void Draw(Color color) override;
};

class Slime: public Solid
{
    public:
    Slime(Rectangle rec);
    void Draw(Color color) override;
};