#ifndef ASTARSEARCH_H
#define ASTARSEARCH_H
#include <vector>
#include "mazegenerator.h"

std::vector<std::pair<int, int>> AStarSearch(const std::vector<std::vector<int>>& maze, int startX, int startY, int endX, int endY);

#endif // ASTARSEARCH_H
