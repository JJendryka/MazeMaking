#include <stdlib.h>
#include "MazeRecursiveBacktracker.h"

int main()
{
    srand(time(0));
    MazeRecursiveBacktracker maze;
    maze.createMaze();
    maze.saveMaze();
}