#pragma once
#include "raylib.h"
#include <iostream>

class Player
{
    private:
    Rectangle rect;
    float thickness;
    float rotation;
    Color color;
    public:
    Player(Vector2 pos, float thickness, Color color);
    Rectangle GetRect();
    void Draw();
    void Move(float dt);
    void CheckWallColl();
    void CheckObjColl();
    void Update(float dt);

    ~Player();
};