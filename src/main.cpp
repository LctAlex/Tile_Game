#include <iostream>
#include <vector>
#include <fstream>
#include "raylib.h"
#include "player.hpp"
#include "objects.hpp"
#include "utils.hpp"

#define AIR '0' //not gonna use it really
#define SOLID '1'
#define TRAP '2'
#define SLIME '3'

const int screenW = 1000;
const int screenH = 800;

std::vector<Solid*> LoadFileToVec(const char*fileName) //should add it to "utils"
{
    std::fstream file = OpenFileI(fileName);

    std::vector<Solid*> rec;
    std::string temp;
    int totalW, totalH;
    
    for(totalH = 0; std::getline(file, temp); totalH++);
    file.clear();
    file.seekg(0);
    
    int x, y = 0;
    Rectangle tempRec;
    while(std::getline(file, temp))
    {
        totalW = temp.length();
        for(x = 0; x < totalW; x++)
        {
            if(temp[x] == SOLID)
            {
                int tempStartX = x;
                while(temp[x] == SOLID) x++;
                tempRec = {tempStartX*(float)screenW/totalW, y*(float)screenH/totalH,
                                (x-tempStartX)*(float)screenW/totalW, (float)screenH/totalH};
                rec.emplace_back(new Solid(tempRec));
            }
            if(temp[x] == TRAP)
            {
                int tempStartX = x;
                while(temp[x] == TRAP) x++;
                tempRec = {tempStartX*(float)screenW/totalW, y*(float)screenH/totalH,
                                (x-tempStartX)*(float)screenW/totalW, (float)screenH/totalH};
                rec.emplace_back(new Trap(tempRec));
                x--;
            }
            if(temp[x] == SLIME)
            {
                int tempStartX = x;
                while(temp[x] == SLIME) x++;
                tempRec = {tempStartX*(float)screenW/totalW, y*(float)screenH/totalH,
                                (x-tempStartX)*(float)screenW/totalW, (float)screenH/totalH};
                rec.emplace_back(new Slime(tempRec));
                x--;
            }
        }
        y++;
    }

    return rec;
}

int main()
{
    std::string map[] = {};
    std::vector<Solid*> recVec = LoadFileToVec("levels/map1.txt");

    Player player({screenW/2, screenH/2}, 50, PINK);

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
                    o->SetBool(); //WORKS, I'll rewrite "objects.cpp", I'll make separate files for each class to make it clean
                }
            }
        }

        BeginDrawing();
        ClearBackground(WHITE);
        for(auto r : recVec)
        {
            r->Draw();
            r->Update();
        }
        player.Update(dt);
        EndDrawing();
    }

    for(auto r: recVec)
    {
        delete(r);
    }
    CloseWindow();
    return 0;
}