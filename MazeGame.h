#ifndef MAZEGAME_H
#define MAZEGAME_H

#include <QWidget>
#include <QPixmap>
#include <QTimer>
#include <QElapsedTimer>
#include <qlabel.h>
#include "struct.h"

class QPushButton;

class MazeGame : public QWidget {
    Q_OBJECT

public:
    MazeGame(int width, int length, int seeds, const int mode,bool isAllowNesting,int ID, QWidget *parent = nullptr);
    void loadSave(int playerX, int playerY, int endX, int endY, std::vector<Maze> mazes,int ID,int layers);

protected:
    void paintEvent(QPaintEvent *event) override;
    void keyPressEvent(QKeyEvent *event) override;

private slots:
    void updateAnimation();
    void saveAndQuit();

private:
    enum Direction { Up, Down, Left, Right };
    Direction currentDirection;

    int layers;
    bool isAllowNesting;
    int width;
    int length;
    int seeds;
    int mode;
    int isFindPath;

    // Player position
    int playerX, playerY;
    int targetX, targetY;
    bool isMoving;
    float moveProgress;

    // Viewport
    float viewportX;
    float viewportY;
    int viewportWidth;
    int viewportHeight;

    // AstarSearch
    std::vector<std::pair<int, int>> path;  // 存储A*算法找到的路径
    bool isAutoMoving;                      // 标记是否处于自动移动状态
    int pathIndex;                          // 当前移动到路径中的哪个位置

    void updateViewport();
    void startMoving(int newX, int newY);
    void generateMaze();
    void setFurthestEndPoint();
    QPixmap adjustBrightness(const QPixmap &pixmap, float brightnessFactor, int row, int col,std::vector<std::pair<int,int>> lightblock1);
    QPixmap adjustBrightness_DAY(const QPixmap &pixmap, float brightnessFactor);
    float calculateLightDistance(int startX, int startY, int targetX, int targetY);

    // Maze data
    std::vector<std::vector<int>> maze;

    std::vector<Maze> mazes;

    int endX, endY;

    // Graphics
    QPixmap roomPixmap1, roomPixmap2, doorPixmap,roomPixmap3, roomPixmap4;
    QPixmap upAnimation[3], downAnimation[3];
    std::vector<QPixmap> leftAnimation, rightAnimation;
    int currentFrame;
    QTimer *timer;
    QLabel *layerLabel;
    QLabel *timerLabel;
    float timerSeconds;


    // Animation timing
    int animationCounter;

    // UI Elements
    QWidget *gameWidget;          // 游戏区域
    QPushButton *saveQuitButton;

    int ID;
    bool isTaskMaze;
};

#endif // MAZEGAME_H
