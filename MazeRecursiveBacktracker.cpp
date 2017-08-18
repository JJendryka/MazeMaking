#include <algorithm>
#include <array>
#include <stack>
#include <iostream>
#include "MazeRecursiveBacktracker.h"
#include "BMPHelper.h"

MazeRecursiveBacktracker::MazeRecursiveBacktracker() {
    grid.resize(mazeWidth * mazeHeight);
    std::fill(grid.begin(), grid.end(), std::bitset<5>(0));
}

void MazeRecursiveBacktracker::createMaze() {
    struct Pos {unsigned int x, y, state; std::array<short, 4> order;};
    std::stack<Pos> states;

    Pos pos = {0, 0, 0, randomDirections()};
    states.push(pos);

    while (!states.empty()) {
        auto top = states.top();
        states.pop();

        grid[top.x + top.y * mazeWidth][4] = 1;

        if(top.state < 3) states.push({top.x, top.y, top.state+1, top.order});

        if(top.order[top.state] == 0 && top.x!=mazeWidth-1) {
            if (!(grid[(top.x + 1) + top.y * mazeWidth][4])) {
                states.push({top.x + 1, top.y, 0, randomDirections()});
                grid[top.x + top.y * mazeWidth][0] = 1;
                grid[(top.x + 1) + top.y * mazeWidth][2] = 1;
            }
        }
        if(top.order[top.state] == 1 && top.y!=0) {
            if(!(grid[top.x + (top.y-1) * mazeWidth][4])) {
                states.push({top.x, top.y-1, 0, randomDirections()});
                grid[top.x + top.y * mazeWidth][1] = 1;
                grid[top.x + (top.y-1) * mazeWidth][3] = 1;
            }
        }
        if(top.order[top.state] == 2 && top.x!=0) {
            if(!(grid[(top.x-1) + top.y * mazeWidth][4])) {
                states.push({top.x-1, top.y, 0, randomDirections()});
                grid[top.x + top.y * mazeWidth][2] = 1;
                grid[(top.x-1) + top.y * mazeWidth][0] = 1;
            }
        }
        if(top.order[top.state] == 3 && top.y!=mazeHeight-1) {
            if(!(grid[top.x + (top.y+1) * mazeWidth][4])) {
                states.push({top.x, top.y+1, 0, randomDirections()});
                grid[top.x + top.y * mazeWidth][3] = 1;
                grid[top.x + (top.y+1) * mazeWidth][1] = 1;
            }
        }
    }
    grid[0][1] = 1;
    grid[mazeWidth*mazeHeight-1][3] = 1;
}

void MazeRecursiveBacktracker::saveMaze() {
    std::cout<<grid.size();

    for (unsigned int y = 0; y < mazeWidth; y++)
    {
        for (unsigned int x = 0; x < mazeHeight; x++)
        {
            setPixel(x*4, y*4, true);
            setPixel(x*4+3, y*4, true);
            setPixel(x*4, y*4+3, true);
            setPixel(x*4+3, y*4+3, true);
            setPixel(x*4+1, y*4+1, false);
            setPixel(x*4+2, y*4+1, false);
            setPixel(x*4+1, y*4+2, false);
            setPixel(x*4+2, y*4+2, false);

            if(grid[x + y * mazeWidth][0]) {
                setPixel(x*4+3, y*4+1, false);
                setPixel(x*4+3, y*4+2, false);
            }
            else {
                setPixel(x*4+3, y*4+1, true);
                setPixel(x*4+3, y*4+2, true);
            }

            if(grid[x + y * mazeWidth][1]) {
                setPixel(x*4+1, y*4, false);
                setPixel(x*4+2, y*4, false);
            }
            else {
                setPixel(x*4+1, y*4, true);
                setPixel(x*4+2, y*4, true);
            }
            if(grid[x + y * mazeWidth][2]) {
                setPixel(x*4, y*4+1, false);
                setPixel(x*4, y*4+2, false);
            }
            else {
                setPixel(x*4, y*4+1, true);
                setPixel(x*4, y*4+2, true);
            }
            if(grid[x + y * mazeWidth][3]) {
                setPixel(x*4+1, y*4+3, false);
                setPixel(x*4+2, y*4+3, false);
            }
            else {
                setPixel(x*4+1, y*4+3, true);
                setPixel(x*4+2, y*4+3, true);
            }
        }
    }

    BMPHelper::bmp_generator("./test.bmp", mazeWidth*4, mazeHeight*4, (unsigned char*)buffer);
}

void MazeRecursiveBacktracker::setPixel(unsigned int x, unsigned int y, bool color) {
    buffer[x][y].r = buffer[x][y].g = buffer[x][y].b = color ? 0 : 255;
}

std::array<short, 4> MazeRecursiveBacktracker::randomDirections() {
    std::array<short, 4> directions = {0, 1, 2, 3};
    std::random_shuffle(directions.begin(), directions.end());
    return directions;
};


