#include <vector>
#include <algorithm>
#include <random>
#include <ctime>
#include <stack>
#include <tuple>
#include "mazegenerator.h"

MazeGenerator::MazeGenerator(int width, int height, int seeds,int mode,bool isAllowNesting) {
    this->width = width;
    this->height = height;
    this->seeds = seeds;
    this->mode=mode;
    this->isAllowNesting=isAllowNesting;

    // 初始化随机数生成器
    std::mt19937 rng(seeds);  // 使用 Mersenne Twister 随机数生成器
    this->rng = rng;
    std::srand(seeds);

    // 初始化 Union-Find 数据结构
    parent.resize(width * height, -1);
    rank.resize(width * height, 0);
    maze.resize(height, std::vector<int>(width, 0));  // 初始化迷宫为全墙壁
}

// Generate maze using DFS
std::vector<std::vector<int>> MazeGenerator::generateDFS() {
    maze = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    std::stack<std::pair<int, int>> stack;
    stack.push({1, 1});  // Starting point
    maze[1][1] = 1;

    while (!stack.empty()) {
        auto [x, y] = stack.top();
        std::vector<std::pair<int, int>> neighbors;

        // Check all four possible directions
        if (x > 2 && maze[y][x - 2] == 0) neighbors.push_back({x - 2, y});
        if (x < width - 3 && maze[y][x + 2] == 0) neighbors.push_back({x + 2, y});
        if (y > 2 && maze[y - 2][x] == 0) neighbors.push_back({x, y - 2});
        if (y < height - 3 && maze[y + 2][x] == 0) neighbors.push_back({x, y + 2});

        if (!neighbors.empty()) {
            // Randomly choose a neighbor using modern C++ random
            std::uniform_int_distribution<int> dist(0, neighbors.size() - 1);
            auto [nx, ny] = neighbors[dist(rng)];
            maze[ny][nx] = 1;
            maze[(y + ny) / 2][(x + nx) / 2] = 1;  // Break the wall between
            stack.push({nx, ny});
        } else {
            stack.pop();
        }
    }

    return maze;
}

// Generate maze using Prim's algorithm
std::vector<std::vector<int>> MazeGenerator::generatePrim() {
    maze = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    std::vector<std::tuple<int, int, int, int>> walls;
    maze[1][1] = 1;

    // Add walls of the starting point
    addWalls_prim(1, 1, walls);

    while (!walls.empty()) {
        int wx, wy, px, py;
        std::tie(wx, wy, px, py) = walls[rand() % walls.size()];

        if (maze[wy][wx] == 0) {
            maze[wy][wx] = 1;
            maze[(wy + py) / 2][(wx + px) / 2] = 1;
            addWalls_prim(wx, wy, walls);
        }

        walls.erase(std::remove(walls.begin(), walls.end(), std::make_tuple(wx, wy, px, py)), walls.end());
    }

    return maze;
}

// Generate maze using Kruskal's algorithm
std::vector<std::vector<int>> MazeGenerator::generateKruskal() {
    maze = std::vector<std::vector<int>>(height, std::vector<int>(width, 0));
    std::vector<std::tuple<int, int, int, int>> walls;

    // Initialize Union-Find
    for (int y = 1; y < height; y += 2) {
        for (int x = 1; x < width; x += 2) {
            int index = y * width + x;
            parent[index] = index;  // Each cell is its own parent
        }
    }

    // Collect all walls
    for (int y = 1; y < height; y += 2) {
        for (int x = 1; x < width; x += 2) {
            addWalls_kruskal(x, y, walls);
        }
    }

    // Shuffle walls randomly using modern C++ random
    std::shuffle(walls.begin(), walls.end(), rng);

    // Build the maze using Kruskal's algorithm
    for (auto& wall : walls) {
        int wx, wy, px, py;
        std::tie(wx, wy, px, py) = wall;

        int cell1 = wy * width + wx;
        int cell2 = py * width + px;

        if (findSet(cell1) != findSet(cell2)) {
            // These two cells belong to different sets, merge them
            maze[wy][wx] = 1;
            maze[py][px] = 1;
            unionSets(cell1, cell2);  // Merge sets
        }
    }

    return maze;
}

// Union-Find with path compression
void MazeGenerator::unionSets(int i, int j) {
    int rootI = findSet(i);
    int rootJ = findSet(j);

    if (rootI != rootJ) {
        // Union by rank
        if (rank[rootI] > rank[rootJ]) {
            parent[rootJ] = rootI;
        } else if (rank[rootI] < rank[rootJ]) {
            parent[rootI] = rootJ;
        } else {
            parent[rootJ] = rootI;
            rank[rootI]++;
        }
    }
}

// Find the root of a set with path compression
int MazeGenerator::findSet(int i) {
    if (parent[i] != i) {
        parent[i] = findSet(parent[i]);  // Path compression
    }
    return parent[i];
}

// 添加一个格子周围的墙壁到墙壁列表
// Add walls of a given cell to the wall list
void MazeGenerator::addWalls_prim(int x, int y, std::vector<std::tuple<int, int, int, int>>& walls) {
    if (x > 2 && maze[y][x - 2] == 0) walls.push_back({x - 2, y, x, y});
    if (x < width - 3 && maze[y][x + 2] == 0) walls.push_back({x + 2, y, x, y});
    if (y > 2 && maze[y - 2][x] == 0) walls.push_back({x, y - 2, x, y});
    if (y < height - 3 && maze[y + 2][x] == 0) walls.push_back({x, y + 2, x, y});
}

void MazeGenerator::addWalls_kruskal(int x, int y, std::vector<std::tuple<int, int, int, int>>& walls) {
    if (x > 1) walls.push_back({x - 1, y, x, y});  // Left
    if (x < width - 2) walls.push_back({x + 1, y, x, y});  // Right
    if (y > 1) walls.push_back({x, y - 1, x, y});  // Up
    if (y < height - 2) walls.push_back({x, y + 1, x, y});  // Down
}

std::vector<Maze> MazeGenerator::generateMazes() {
    std::vector<Maze> mazes;
    std::vector<door> doors;
    std::mt19937 gen(seeds);

    // 生成第一个主迷宫
    Maze maze1;
    maze1.ID = 1;
    maze1.isTaskMaze = false;

    // 生成迷宫
    std::vector<std::vector<int>> maze;
    switch (mode) {
    case 0: maze = generateDFS(); break;
    case 1: maze = generateKruskal(); break;
    case 2: maze = generatePrim(); break;
    default: maze = generateDFS(); break;
    }

    // 随机生成任务迷宫数
    std::uniform_int_distribution<> dis(2, 5);
    int taskMazeCount = dis(gen);
    int taskMazeCount1 = taskMazeCount;
    int idtmp = 1;

    // 生成任务迷宫
    while (taskMazeCount != 0) {
        std::uniform_int_distribution<> dis1(0, height - 1);
        std::uniform_int_distribution<> dis2(0, width - 1);

        int y = dis1(gen);
        int x = dis2(gen);

        if (maze[y][x] == 1) {  // 找到一个可放门的位置
            maze[y][x] = 10;  // 设置门
            taskMazeCount--;
            door door1;
            door1.isExit = false;
            door1.locationX = x;
            door1.locationY = y;
            door1.towardMaze = idtmp + 1;
            idtmp++;
            doors.push_back(door1);
        }
    }

    maze1.maze = maze;
    maze1.doors=doors;
    mazes.push_back(maze1);
    doors.clear();
    idtmp=1;
    // 生成其他任务迷宫
    while (taskMazeCount1) {
        idtmp++;
        maze1.ID = idtmp;
        maze1.isTaskMaze = true;

        switch (mode) {
        case 0: maze = generateDFS(); break;
        case 1: maze = generateKruskal(); break;
        case 2: maze = generatePrim(); break;
        default: maze = generateDFS(); break;
        }

        maze1.maze = maze;
        int i = 1;

        while (i) {
            std::uniform_int_distribution<> dis1(0, height - 1);
            std::uniform_int_distribution<> dis2(0, width - 1);

            int y = dis1(gen);
            int x = dis2(gen);

            if (maze[y][x] == 1) {  // 找到一个可放门的位置
                maze[y][x] = 10;  // 设置门
                i--;

                door door1;
                door1.isExit = true;
                door1.locationX = x;
                door1.locationY = y;
                door1.towardMaze = 1;
                doors.push_back(door1);
            }
        }
        maze1.maze=maze;
        maze1.doors=doors;
        mazes.push_back(maze1);
        doors.clear();
        taskMazeCount1--;
    }

    return mazes;
}

