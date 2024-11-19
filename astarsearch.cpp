#include "astarsearch.h"
#include <algorithm>
#include <queue>
#include <vector>
#include <cmath>
#include <utility>

struct Node {
    int x, y;
    int g, h;
    int parentX, parentY;  // 存储父节点的坐标
    int f() const { return g + h; }

    bool operator<(const Node& other) const {
        return f() > other.f();
    }

    // 构造函数
    Node(int x, int y, int g, int h, int parentX = -1, int parentY = -1)
        : x(x), y(y), g(g), h(h), parentX(parentX), parentY(parentY) {}
};


    // 计算曼哈顿距离作为启发式函数
    int heuristic(int x1, int y1, int x2, int y2) {
        return abs(x1 - x2) + abs(y1 - y2);
    }

    std::vector<std::pair<int, int>> AStarSearch(const std::vector<std::vector<int>>& maze,
                                                 int startX, int startY,
                                                 int endX, int endY) {
        auto cmp = [](const Node& a, const Node& b) {
            return a.f() > b.f();
        };
        std::priority_queue<Node, std::vector<Node>, decltype(cmp)> openList(cmp);

        std::vector<std::vector<bool>> closedList(maze.size(), std::vector<bool>(maze[0].size(), false));

        // 用于记录节点的父节点坐标
        std::vector<std::vector<std::pair<int, int>>> parentMap(maze.size(),
                                                                std::vector<std::pair<int, int>>(maze[0].size(), {-1, -1}));

        // 开始节点
        openList.push(Node(startX, startY, 0, heuristic(startX, startY, endX, endY)));

        std::vector<std::pair<int, int>> directions = {
            {-1, 0}, {1, 0}, {0, -1}, {0, 1}
        };

        while (!openList.empty()) {
            Node current = openList.top();
            openList.pop();

            // 如果已经到达终点
            if (current.x == endX && current.y == endY) {
                std::vector<std::pair<int, int>> path;
                int x = current.x;
                int y = current.y;
                while (x != -1 && y != -1) {
                    path.push_back({x, y});
                    auto [px, py] = parentMap[y][x];
                    x = px;
                    y = py;
                }
                std::reverse(path.begin(), path.end());
                return path;  // 返回找到的路径
            }

            // 标记该节点为已访问
            closedList[current.y][current.x] = true;

            // 检查周围四个方向
            for (const auto& [dx, dy] : directions) {
                int newX = current.x + dx;
                int newY = current.y + dy;

                if (newX < 0 || newX >= maze[0].size() || newY < 0 || newY >= maze.size()
                    || maze[newY][newX] == 0 || closedList[newY][newX]) {
                    continue;
                }

                int gNew = current.g + 1;
                int hNew = heuristic(newX, newY, endX, endY);
                openList.push(Node(newX, newY, gNew, hNew));

                // 记录父节点
                parentMap[newY][newX] = {current.x, current.y};
            }
        }

        return {};
    }

