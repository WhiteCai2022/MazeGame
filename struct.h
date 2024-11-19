#ifndef STRUCT_H
#define STRUCT_H

#include <vector>

struct door{
    bool isExit;
    int locationX;
    int locationY;
    int towardMaze;
};

struct Maze{
    std::vector<std::vector<int>> maze;
    int ID;
    bool isTaskMaze;
    std::vector<door> doors;
};


#endif // STRUCT_H
