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
