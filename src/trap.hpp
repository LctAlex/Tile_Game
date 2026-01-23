#pragma once
#include "solid.hpp"

class Trap : public Solid
{
    private:
    Vector2 spike[3];
    bool rise;
    public:
    Trap(Rectangle rec);
    void SetBool(bool val) override;
    void Draw(Color color) override;
    void Update() override;
};