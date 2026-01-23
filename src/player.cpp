#include "player.hpp"

Player::Player(Vector2 pos, float thickness, Color color):hitbox({pos.x, pos.y, thickness, thickness}),color(color)
{
    rotation = 0.0f;
}

void Player::Draw()
{
    DrawRectangleRec(hitbox, color);
}

bool Player::Update(float dt)
{
    bool moving = true;
    if(IsKeyDown(KEY_LEFT)) hitbox.x -= hitbox.width * 3 * dt;
    else if(IsKeyDown(KEY_RIGHT)) hitbox.x += hitbox.width * 3 * dt;
    else moving = false;
    return moving;
}

Rectangle Player::GetHitbox() { return hitbox; }

void Player::CheckWallColl()
{
    if(hitbox.x < 0) hitbox.x = 0;
    else if(hitbox.x + hitbox.width > screenW) hitbox.x = screenW - hitbox.width;
    else if((hitbox.y + hitbox.height/2) > screenH) std::cout << "DEAD\n";
    std::cout << "Checking...\n";
}

Player::~Player(){}