#pragma once
#include "solid.hpp"

class Slime : public Solid
{
    public:
    Slime(Rectangle rec);
    void Draw(Color color) override;
};