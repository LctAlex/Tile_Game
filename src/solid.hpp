#pragma once
#include "raylib.h"
#include <iostream> //for debugging

class Solid
{
    protected:
    Rectangle rec;
    public:
    Solid(Rectangle rec);
    Rectangle GetRec(); //need it?
    virtual void SetBool(bool val);
    virtual void Draw(Color color = BLACK);
    virtual void Update();
    virtual ~Solid();
};