#include <iostream>
#include <vector>
#include <fstream>

#include "raylib.h"
#include "player.hpp"
#include "utils.hpp" //screen size, block types, file loading

int main()
{
    std::vector<Solid*> recVec = LoadFileToVec("levels/map1.txt");

    Player player({screenW-150, screenH-150}, 50, PINK);

    InitWindow(screenW, screenH, "Maps\nLoL");
    SetTargetFPS(60);
    while(!WindowShouldClose())
    {
        float dt = GetFrameTime();

        if(IsKeyPressed(KEY_ENTER))
        {
            for(auto o: recVec)
            {
                if(typeid(*o) == typeid(Trap))
                {
                    o->SetBool(true);
                }
            }
        }
        
        player.Update(recVec, dt);

        BeginDrawing();
        ClearBackground(WHITE);
        for(auto r : recVec)
        {
            r->Draw();
            r->Update();
        }
        player.Draw();
        DrawFPS(50, 50);
        EndDrawing();
    }

    for(auto r: recVec)
    {
        delete(r);
    }
    CloseWindow();
    return 0;
}