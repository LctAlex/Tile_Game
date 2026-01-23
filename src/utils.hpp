#pragma once
#include <fstream>
#include <vector>
#include "raylib.h"
#include "objects.hpp"
#include "data.hpp"

std::fstream OpenFileI(const char* fileName);

std::vector<Solid*> LoadFileToVec(const char*fileName);