#include "MazeRecursiveBacktracker.h"
#include "MazePrim.h"
#include <iostream>

int main()
{
    std::cout<<"Welcome in maze making program!\n"
             <<"Choose one of following algorithms:\n"
             <<" 1) Recursive Backtracker\n"
             <<" 2) Prim\n";
    int algorithm;
    std::cin>>algorithm;
    if (algorithm > 2) {
        std::cout<<"Bad algorithm number! Choose 1 or 2";
        return 0;
    }
    std::cout<<"Choose size of maze: (Interactive if below 25)\n";
    int size;
    std::cin>>size;
    if(size < 5) {
        std::cout<<"Choose bigger size!";
        return 0;
    }
    std::cout<<"Choose difficulty (0-100):\n";
    unsigned short difficulty;
    std::cin>>difficulty;
    if (difficulty > 100) {
        std::cout<<"Difficulty should be between 0 and 100\n";
        return 0;
    }
    std::cout<<"Hold any key to progress. Exit on esc\n";
    switch (algorithm) {
        case 1: {
            MazeRecursiveBacktracker maze(size, difficulty);
            maze.createMaze();
            break;
        }
        case 2: {
            MazePrim maze(size, difficulty);
            maze.createMaze();
            break;
        }
        default: {
            std::cout << "Bad input! Choose between 1 and 3\n";
            break;
        }
    }
}