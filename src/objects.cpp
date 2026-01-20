#include "objects.hpp"

//Base function (SOLID) will have multiple configs
//Each object will:
//Have a Draw function
//Have an Update function (if changing)

Solid::Solid(Rectangle rec):rec(rec){}
Rectangle Solid::GetRec(){return rec;}
void Solid::SetBool(){}
bool Solid::GetBool(){}
void Solid::Draw(Color color)
{
    DrawRectangleRec(rec, color);
    DrawRectangleLinesEx(rec, 0.5f, RED); //will be removed at the end
}
void Solid::Update(){}
Solid::~Solid(){}
//
Trap::Trap(Rectangle rec):Solid(rec)
{
    spike[0] = {rec.x, rec.y+rec.height}; //left-down
    spike[1] = {rec.x+rec.width, rec.y+rec.height}; //right-down
    spike[2] = {rec.x+rec.width/2, rec.y}; //middle-up

    rising = false;
}
Vector2 Trap::GetSpike(int index)
{
    return spike[index];
}
void Trap::RiseSpike()
{
    if(spike[0].y >= rec.y)
    {
        for(int i = 0; i < 3; i++)
        {
            spike[i].y -= rec.y/3 * GetFrameTime();
        }
    }
    else 
    {
        rising = false;
        std::cout << "Stopped rising triangle\n";
    }
}
void Trap::SetBool()
{
    rising = true;
}
void Trap::Update() {if(rising)RiseSpike();}
void Trap::Draw(Color color)
{
    Solid::Draw(YELLOW);
    DrawTriangle(spike[0], spike[1], spike[2], BLUE);
}
//
Slime::Slime(Rectangle rec):Solid(rec){}
void Slime::Draw(Color color)
{
    Solid::Draw(DARKGREEN);
}
//
