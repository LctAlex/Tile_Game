#include "utils.hpp"

std::fstream OpenFileI(const char* fileName)
{
    std::fstream file;
    file.open(fileName, std::ios::in);
    if(!file.is_open())
    {
        perror("Failed to open file!");
        exit(EXIT_FAILURE);
    }
    return file;
}

std::vector<Solid*> LoadFileToVec(const char*fileName)
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