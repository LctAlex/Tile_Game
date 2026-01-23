#include "trap.hpp"

Trap::Trap(Rectangle rec):Solid(rec)
{
    spike[0] = {rec.x, rec.y+rec.height}; //left-down
    spike[1] = {rec.x+rec.width, rec.y+rec.height}; //right-down
    spike[2] = {rec.x+rec.width/2, rec.y}; //middle-up

    rise = false;
}
void Trap::SetBool(bool val)
{
    if(!rise) rise = val;
}
void Trap::Draw(Color color)
{
    Solid::Draw(YELLOW);
    DrawTriangle(spike[0], spike[1], spike[2], BLUE);
}
void Trap::Update()
{
    if(rise && spike[0].y > rec.y)
    {
        for(int i = 0; i < 3; i++)
        {
            spike[i].y -= rec.height*2 * GetFrameTime();
        }
    }
}