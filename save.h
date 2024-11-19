#ifndef SAVE_H
#define SAVE_H

#include <fstream>
#include <iostream>
#include "struct.h"
#include "json.hpp"

class Save
{
public:
    // 默认构造函数
    Save()
        : length(0), width(0), seeds(0), mode(0),
        playerX(0), playerY(0), endX(0), endY(0)
    {}

    // 带参数的构造函数
    Save(int length, int width, int seeds, int mode, const std::vector<Maze>& mazes,
         int playerX, int playerY, int endX, int endY,int ID,int layers)
        : length(length), width(width), seeds(seeds), mode(mode), mazes(mazes),
        playerX(playerX), playerY(playerY), endX(endX), endY(endY),ID(ID),layers(layers) {}

    // 保存数据到文件
    void saveToFile(const std::string& filename = "latestSave.json") {
        nlohmann::json jsonData;

        // 基础数据
        jsonData["layers"] = layers;
        jsonData["currentID"] = ID;
        jsonData["length"] = length;
        jsonData["width"] = width;
        jsonData["seeds"] = seeds;
        jsonData["mode"] = mode;
        jsonData["playerX"] = playerX;
        jsonData["playerY"] = playerY;
        jsonData["endX"] = endX;
        jsonData["endY"] = endY;

        // 迷宫数据 - 保存每个迷宫
        nlohmann::json mazeData;
        for (const auto& maze : mazes) {
            nlohmann::json singleMaze;
            singleMaze["ID"] = maze.ID;
            singleMaze["isTaskMaze"] = maze.isTaskMaze;
            singleMaze["maze"] = maze.maze;  // 保存二维迷宫数组

            // 保存门的数据
            nlohmann::json doorsData;
            for (const auto& d : maze.doors) {
                nlohmann::json doorData;
                doorData["isExit"] = d.isExit;
                doorData["locationX"] = d.locationX;
                doorData["locationY"] = d.locationY;
                doorData["towardMaze"] = d.towardMaze;
                doorsData.push_back(doorData);
            }
            singleMaze["doors"] = doorsData;

            mazeData.push_back(singleMaze); // 将迷宫添加到迷宫列表
        }
        jsonData["mazes"] = mazeData;

        // 将JSON数据写入文件
        std::ofstream outFile(filename);
        if (!outFile.is_open()) {
            std::cerr << "无法打开文件!" << std::endl;
            return;
        }
        outFile << jsonData.dump(4); // 格式化输出，缩进4个空格
        outFile.close();
        std::cout << "保存成功！" << std::endl;
    }

    // 从文件加载数据
    bool loadFromFile(const std::string& filename = "latestSave.json") {
        std::ifstream inFile(filename);
        if (!inFile.is_open()) {
            std::cerr << "无法打开文件!" << std::endl;
            return false;
        }

        nlohmann::json jsonData;
        inFile >> jsonData;

        // 读取基础数据
        layers = jsonData["layers"];
        ID  = jsonData["currentID"];
        length = jsonData["length"];
        width = jsonData["width"];
        seeds = jsonData["seeds"];
        mode = jsonData["mode"];
        playerX = jsonData["playerX"];
        playerY = jsonData["playerY"];
        endX = jsonData["endX"];
        endY = jsonData["endY"];

        // 读取多个迷宫数据
        mazes.clear(); // 清空已有的迷宫数据
        for (const auto& mazeJson : jsonData["mazes"]) {
            Maze maze;
            maze.ID = mazeJson["ID"];
            maze.isTaskMaze = mazeJson["isTaskMaze"];
            maze.maze = mazeJson["maze"].get<std::vector<std::vector<int>>>();

            // 读取门的数据
            for (const auto& doorJson : mazeJson["doors"]) {
                door d;
                d.isExit = doorJson["isExit"];
                d.locationX = doorJson["locationX"];
                d.locationY = doorJson["locationY"];
                d.towardMaze = doorJson["towardMaze"];
                maze.doors.push_back(d);
            }

            mazes.push_back(maze); // 将迷宫添加到 mazes 列表
        }

        inFile.close();
        std::cout << "文件读取成功！" << std::endl;
        return true;
    }

    // Getters
    int getLength() const { return length; }
    int getWidth() const { return width; }
    int getSeeds() const { return seeds; }
    int getMode() const { return mode; }
    std::vector<Maze> getMazes() const { return mazes; }
    int getPX() const { return playerX; }
    int getPY() const { return playerY; }
    int getEndX() const { return endX; }
    int getEndY() const { return endY; }
    int getID() const {return ID;}
    int getLayers() const {return layers;}

private:
    int length, width, seeds, mode;
    std::vector<Maze> mazes; // 存储多个迷宫
    int playerX, playerY;
    int endX, endY,ID,layers;
};


#endif // SAVE_H
