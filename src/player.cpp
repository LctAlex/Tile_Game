#include "player.hpp"

Player::Player(Vector2 pos = {100, 100}, float thickness = 50, Color color = PINK)
:thickness(thickness), color(color)
{
    rotation = 0.0f;
    rect = {pos.x, pos.y, thickness, thickness};
}

Rectangle Player::GetRect()
{
    return rect;
}

void Player::Draw()
{
    DrawRectangleRec(rect, color);
}

void Player::Move(float dt)
{
    if(IsKeyDown(KEY_RIGHT)) rect.x += 3.5 * dt * 50;
    if(IsKeyDown(KEY_LEFT)) rect.x -= 3.5f * dt * 50;
    if(IsKeyDown(KEY_DOWN)) rect.y += 3.5f * dt * 50;
    if(IsKeyDown(KEY_UP)) rect.y -= 3.5f * dt * 50;
}

void Player::Update(float dt) //check collisions
{
    Draw();
    Move(dt);
}

Player::~Player(){}