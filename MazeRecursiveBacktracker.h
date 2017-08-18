#pragma once

#include <vector>
#include <bitset>
#include "BMPHelper.h"
#include <array>
#include "Variables.h"

class MazeRecursiveBacktracker {
public:
    MazeRecursiveBacktracker();
    void createMaze();
    void saveMaze();

private:
    void setPixel(unsigned int x, unsigned int y, bool color);
    std::array<short, 4> randomDirections();

    std::vector<std::bitset<5>> grid;

    BMPHelper::RGB_data buffer[mazeWidth*4][mazeHeight*4];
};