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
    public:
    Player(Vector2 pos, float thickness, Color color);

    void Draw();
    bool Update(float dt); //stuff will only happen when we update, should turn back to void, and implement bool moving inside Update, and check based on that inside Update()
    Rectangle GetHitbox();
    void CheckWallColl();
    void CheckObjColl(std::vector<Solid*> &list);

    ~Player();
};