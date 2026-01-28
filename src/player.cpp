#include "player.hpp"

Player::Player(Vector2 pos, float thickness, Color color):hitbox({pos.x, pos.y, thickness, thickness}),color(color)
{
    rotation = 0.0f;
    momentum = {0, 0};
    inAir = true;
}

void Player::Draw()
{
    DrawRectangleRec(hitbox, color);
}

void Player::Update(std::vector<Solid*> &vec, float dt)
{
    Vector2 velocity = {0, 0};
    float speed = 150.f;

    if(IsKeyDown(KEY_LEFT)) 
    {
        velocity.x -= speed;
        momentum.x -= 0.1f;
    }
    if(IsKeyDown(KEY_RIGHT))
    {
        velocity.x += speed;
        momentum.x += 0.1f;
    }
    if(IsKeyPressed(KEY_UP) && momentum.y == 0)
    {
        inAir = true;
    }

    if(momentum.x >= 0.1f || momentum.x <= -0.1f)
    {
        if((momentum.x < 0 && velocity.x > 0) || (momentum.x > 0 && velocity.x < 0))
        {
            momentum.x -= momentum.x*0.1f; //speed up momentum loss
        }
        else momentum.x -= momentum.x*0.02f;
    }
    else momentum.x = 0.0f;

    if(inAir)
    {
        momentum.y -= hitbox.height * 10.f * dt;//this somehow works???
        inAir = false;
    }
    else 
    {
        momentum.y += 0.5f;
    }
    
    ResolveCollX(vec, velocity.x*dt + momentum.x);
    ResolveCollY(vec, /*speed*dt +*/ momentum.y);

}

void Player::ResolveCollX(std::vector<Solid*> &vec, float velX)
{
    hitbox.x += velX;
    for(auto& e: vec)
    {
        if(CheckCollisionRecs(hitbox, e->GetRec()))
        {
            if(velX > 0) //if goes right
            {
                hitbox.x = e->GetRec().x - hitbox.width;
            }
            else if (velX < 0)
            {
                hitbox.x = e->GetRec().x + e->GetRec().width;
            }
            momentum.x = 0;
            break; //leave if collided
        }
    }
}

void Player::ResolveCollY(std::vector<Solid*> &vec, float velY) //rethink
{
    hitbox.y += velY;
    for(auto& e: vec)
    {
        if(CheckCollisionRecs(hitbox, e->GetRec()))
        {
            if(velY > 0) //if goes down
            {
                hitbox.y = e->GetRec().y - hitbox.height;
            }
            else if(velY < 0)
            {
                hitbox.y = e->GetRec().y + e->GetRec().height;
            }
            momentum.y = 0;
            break;
        }
    }
}

Rectangle Player::GetHitbox() { return hitbox; }

Player::~Player(){}