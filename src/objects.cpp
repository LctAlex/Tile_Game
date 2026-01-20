#include "objects.hpp"

Solid::Solid(Rectangle rec):rec(rec){}
Rectangle Solid::GetRec(){return rec;}
void Solid::Draw(Color color)
{
    DrawRectangleRec(rec, color);
    DrawRectangleLinesEx(rec, 0.5f, RED); //removed at the end
}
void Solid::Update()
{
    Solid::Draw(BLACK);
}
Solid::~Solid(){}
//
Trap::Trap(Rectangle rec):Solid(rec)
{
    spike[0] = {rec.x, rec.y+rec.height}; //left-down
    spike[1] = {rec.x+rec.width, rec.y+rec.height}; //right-down
    spike[2] = {rec.x+rec.width/2, rec.y}; //middle-up
}
Vector2 Trap::GetSpike(int index)
{
    return spike[index];
}
void Trap::RiseSpike()
{
    if(spike[0].y >= rec.y && rising)
    {
        for(int i = 0; i < 3; i++)
        {
            spike[i].y -= rec.y/3 * GetFrameTime();
        }
    } else rising = false;
}
void Trap::Update()
{
    Solid::Draw(YELLOW);
    DrawTriangle(spike[0], spike[1], spike[2], BLUE);
}
//
Slime::Slime(Rectangle rec):Solid(rec){}
void Slime::Update()
{
    Solid::Draw(GREEN);
}
//
