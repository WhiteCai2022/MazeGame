#ifndef MAZEGENERATOR_H
#define MAZEGENERATOR_H

#include <random>
#include <vector>
#include <tuple>
#include <cstdlib>
#include <ctime>
#include "struct.h"

class MazeGenerator {
public:
    // 构造函数，初始化迷宫的宽度和高度
    MazeGenerator(int width, int height ,int seeds,int mode,bool isAllowNesting);

    /*switch (mode) {
    case 0:
        maze = Maze1.generateDFS();
        break;
    case 1:
        maze = Maze1.generateKruskal();
        break;
    case 2:
        maze = Maze1.generatePrim();
        break;
    default:
        maze = Maze1.generateDFS();
        break;
    }*/

    std::vector<Maze> generateMazes();
private:


    int width, height; // 迷宫的宽度和高度
    int seeds;
    int mode;
    bool isAllowNesting;
    std::vector<std::vector<int>> maze; // 迷宫数据
    // 使用深度优先搜索算法生成迷宫
    std::vector<std::vector<int>> generateDFS();

    // 使用Prim算法生成迷宫
    std::vector<std::vector<int>> generatePrim();

    // 使用Kruskal算法生成迷宫
    std::vector<std::vector<int>> generateKruskal();
    // 添加给定单元格的墙壁到墙壁列表
    void addWalls_prim(int x, int y, std::vector<std::tuple<int, int, int, int>>& walls);
    void addWalls_kruskal(int x, int y, std::vector<std::tuple<int, int, int, int>>& walls);

    // 查找给定单元格的集合
    int findSet(int i);

    void unionSets(int i, int j);

    // Union-Find 数据结构
    std::vector<int> parent, rank;

    std::mt19937 rng;

    std::vector<Maze> mazes;


};

#endif // MAZEGENERATOR_H
