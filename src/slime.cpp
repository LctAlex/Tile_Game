#include "slime.hpp"

Slime::Slime(Rectangle rec):Solid(rec){}
void Slime::Draw(Color color)
{
    Solid::Draw(DARKGREEN);
}