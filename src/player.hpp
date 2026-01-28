#pragma once
#include <iostream> //for debugging
#include <vector>
#include "raylib.h"
#include "objects.hpp"
#include "data.hpp"

class Player
{
    private:
    Rectangle hitbox;
    float rotation;
    Color color;
    Vector2 momentum;
    bool inAir;
    public:
    Player(Vector2 pos, float thickness, Color color);

    void Draw();
    void Update(std::vector<Solid*> &vec, float dt); //stuff will only happen when we update, should turn back to void, and implement bool moving inside Update, and check based on that inside Update()
    void ResolveCollX(std::vector<Solid*> &vec, float velX);
    void ResolveCollY(std::vector<Solid*> &vec, float velY);
    Rectangle GetHitbox();

    ~Player();
};