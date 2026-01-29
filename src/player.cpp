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
    if(IsKeyPressed(KEY_UP) && momentum.y == 0.f)
    {
        inAir = true;
    }

    if(momentum.x >= 0.1f || momentum.x <= -0.1f) //momentum loss
    {
        if((momentum.x < 0.f && velocity.x > 0.f) || (momentum.x > 0.f && velocity.x < 0.f))
        {
            momentum.x -= momentum.x*0.1f; //speed up momentum loss at turns
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
    
    //momentum+ speed logic MUST be upated/optimized!!!
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
            if(typeid(*e) == typeid(Solid) || typeid(*e) == typeid(Trap))
            {
                if(velX > 0.f) //if goes right
                {
                    hitbox.x = e->GetRec().x - hitbox.width;
                }
                else if (velX < 0.f)
                {
                    hitbox.x = e->GetRec().x + e->GetRec().width;
                }
                momentum.x = 0.f;
            }
            else if(typeid(*e) == typeid(Slime))
            {
                if(velX > 0.f) //if goes right
                {
                    hitbox.x = e->GetRec().x - hitbox.width;
                }
                else if (velX < 0.f)
                {
                    hitbox.x = e->GetRec().x + e->GetRec().width;
                }
                if(abs(momentum.x) < 75.f) momentum.x *= -1.5f;
            }
            break;
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
            if(typeid(*e) == typeid(Solid) || typeid(*e) == typeid(Trap))
            {
                if(velY > 0.f) //if goes down
                {
                    hitbox.y = e->GetRec().y - hitbox.height;
                }
                else if(velY < 0.f)
                {
                    hitbox.y = e->GetRec().y + e->GetRec().height;
                }
                if(typeid(*e) == typeid(Trap) && e->GetRec().y > hitbox.y)
                {
                    e->SetBool(true);
                }
                momentum.y = 0.f;
            }
            else if(typeid(*e) == typeid(Slime))
            {
                if(velY > 0.f)
                {
                    hitbox.y = e->GetRec().y - hitbox.height;
                }
                else if(velY < 0.f)
                {
                    hitbox.y = e->GetRec().y + e->GetRec().height;
                }
                if(abs(momentum.y) > 1.f) momentum.y *= -.75f; //must eliminate hardcodes
                else momentum.y = 0.f;
            }
            break;
        }
    }
}

Rectangle Player::GetHitbox() { return hitbox; }

Player::~Player(){}