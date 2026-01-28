#include "solid.hpp"

Solid::Solid(Rectangle rec):rec(rec){}
Rectangle Solid::GetRec() { return rec; }
void Solid::SetBool(bool val){}
void Solid::Draw(Color color)
{
    DrawRectangleRec(rec, color);
    //DrawRectangleLinesEx(rec, 0.5f, RED); //will be removed at the end
}
void Solid::Update(){}
Solid::~Solid(){}