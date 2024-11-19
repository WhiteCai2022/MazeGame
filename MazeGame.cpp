#include "MazeGame.h"
#include <QPainter>
#include <QKeyEvent>
#include <QMessageBox>
#include <QtMath>
#include "save.h"
#include "mainwindow.h"
#include "mazegenerator.h"
#include <QPushButton>
#include <QVBoxLayout>
#include "astarsearch.h"

MazeGame::MazeGame(int width, int length, int seeds, const int mode, bool isAllowNesting,int ID, QWidget *parent)
    : QWidget(parent),layers(1),
    playerX(1), playerY(1),
    targetX(1), targetY(1),
    isMoving(false), moveProgress(0.0f),
    viewportX(0.0f), viewportY(0.0f),
    currentFrame(0),isAutoMoving(false),
    pathIndex(0)
{
    this->length = length;
    this->width = width;
    this->seeds = seeds;
    this->mode = mode;
    this->isFindPath = 0;
    this->isAllowNesting=isAllowNesting;
    this->ID=ID;


    // 设置窗口大小（可以根据需要调整）
    setFixedSize(800, 800);

    // 初始化视窗尺寸
    viewportWidth = 10;   // 显示10个格子
    viewportHeight = 10;

    generateMaze();
    setFurthestEndPoint();

    // 初始化UI
    saveQuitButton = new QPushButton("保存并退出", this);
    QVBoxLayout *layout = new QVBoxLayout(this);
    layout->addStretch();
    layout->addWidget(saveQuitButton);
    setLayout(layout);

    connect(saveQuitButton, &QPushButton::clicked, this, &MazeGame::saveAndQuit);

    // 加载地板贴图
    roomPixmap1.load("./img/box.png");
    roomPixmap2.load("./img/grass.png");
    roomPixmap3.load("./img/floor-1.png");
    roomPixmap4.load("./img/floor-2.png");
    doorPixmap.load("./img/hole.png");


    // 加载角色动画帧
    upAnimation[0].load("./img/up1.png");
    upAnimation[1].load("./img/up2.png");
    upAnimation[2].load("./img/up3.png");
    downAnimation[0].load("./img/down1.png");
    downAnimation[1].load("./img/down2.png");
    downAnimation[2].load("./img/down3.png");
    leftAnimation = { QPixmap("./img/left1.png"), QPixmap("./img/left2.png"), QPixmap("./img/left3.png") };
    rightAnimation = { QPixmap("./img/right1.png"), QPixmap("./img/right2.png"), QPixmap("./img/right3.png") };

    currentDirection = Down;

    // 初始化定时器
    timer = new QTimer(this);
    connect(timer, &QTimer::timeout, this, &MazeGame::updateAnimation);
}

void MazeGame::updateViewport() {
    // 计算玩家的平滑位置
    float playerPosX = playerX;
    float playerPosY = playerY;

    if (isMoving) {
        playerPosX = (1 - moveProgress) * playerX + moveProgress * targetX;
        playerPosY = (1 - moveProgress) * playerY + moveProgress * targetY;
    }

    // 将视窗中心对准玩家位置
    viewportX = playerPosX - viewportWidth / 2.0f + 0.5f;
    viewportY = playerPosY - viewportHeight / 2.0f + 0.5f;

    // 确保视窗不超出迷宫边界
    if (viewportX < 0)
        viewportX = 0;
    if (viewportY < 0)
        viewportY = 0;
    if (viewportX + viewportWidth > width)
        viewportX = width - viewportWidth;
    if (viewportY + viewportHeight > length)
        viewportY = length - viewportHeight;
}

void MazeGame::paintEvent(QPaintEvent *event) {
    QPainter painter(this);

    // 窗口大小
    int windowWidth = 800;
    int windowHeight = 800;

    // 启用抗锯齿和平滑转换
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setRenderHint(QPainter::SmoothPixmapTransform);

    // 绘制背景
    painter.fillRect(0, 0, windowWidth, windowHeight, Qt::black); // 可以选择其他颜色

    // 每个格子的大小，向上取整，避免像素不足
    float gridSizeXf = static_cast<float>(windowWidth) / viewportWidth;
    float gridSizeYf = static_cast<float>(windowHeight) / viewportHeight;
    int gridSizeX = static_cast<int>(std::ceil(gridSizeXf));
    int gridSizeY = static_cast<int>(std::ceil(gridSizeYf));

    // 绘制迷宫
    for (int row = static_cast<int>(viewportY) - 1; row <= static_cast<int>(viewportY + viewportHeight) + 1; ++row) {
        for (int col = static_cast<int>(viewportX) - 1; col <= static_cast<int>(viewportX + viewportWidth) + 1; ++col) {
            if (row >= 0 && row < length && col >= 0 && col < width) {
                int cellType = maze[row][col];
                QPixmap pixmap;
                std::vector<std::pair<int,int>> lightblock;
                lightblock.push_back(std::pair(playerY,playerX));
                for(int i=0;i<10;i++)
                {
                    for(int j=0;j<10;j++)
                    {
                        if(maze[i][j]==5)
                            lightblock.push_back(std::pair(i,j));
                    }
                }
                if(mazes[ID-1].isTaskMaze){
                    if(cellType == 1)
                        pixmap=roomPixmap3;
                    else if(cellType == 0)
                        pixmap=roomPixmap1;
                    else if(cellType == 10)
                        pixmap=doorPixmap;
                    // 调整亮度并绘制格子
                    // 计算格子与玩家的距离
                    float brightnessFactor =1.0f;
                    float distance = INFINITY;
                    //int distance = abs(row - playerY) + abs(col - playerX);
                    for(int i=0;i<lightblock.size();i++)
                    {
                        float distancetmp = std::sqrt((col - lightblock[i].second) * (col - lightblock[i].second) + (row - lightblock[i].first) * (row - lightblock[i].first));//欧几里得
                        if(distancetmp<distance)
                            distance=distancetmp;
                    }

                    float maxLightDistance=6.0;
                    float maxBrightness=1.0f;
                    float attenuation=0.1;

                    // 如果格子在光源的影响范围内，调整亮度
                    if (distance <= maxLightDistance) {
                        //brightnessFactor = 1.0f - (distance / static_cast<float>(maxLightDistance));
                        brightnessFactor = maxBrightness / (1.0f + distance * distance * attenuation);
                    } else {
                        brightnessFactor = 0.1f;  // 光源范围外，设为暗色
                    }

                    // 调整亮度并绘制格子
                    QPixmap brightPixmap = adjustBrightness(pixmap, brightnessFactor,row,col,lightblock);
                    // 计算绘制位置
                    float drawXf = (col - viewportX) * gridSizeXf;
                    float drawYf = (row - viewportY) * gridSizeYf;
                    int drawX = static_cast<int>(std::floor(drawXf));
                    int drawY = static_cast<int>(std::floor(drawYf));

                    painter.drawPixmap(drawX, drawY, gridSizeX, gridSizeY, brightPixmap);
                }else{
                    if(cellType == 1)
                        pixmap=roomPixmap2;
                    else if(cellType == 0)
                        pixmap=roomPixmap1;
                    else if(cellType == 10)
                        pixmap=doorPixmap;
                    // 调整亮度并绘制格子
                    QPixmap brightPixmap = adjustBrightness_DAY(pixmap, 1.0f);

                    // 计算绘制位置
                    float drawXf = (col - viewportX) * gridSizeXf;
                    float drawYf = (row - viewportY) * gridSizeYf;
                    int drawX = static_cast<int>(std::floor(drawXf));
                    int drawY = static_cast<int>(std::floor(drawYf));

                    painter.drawPixmap(drawX, drawY, gridSizeX, gridSizeY, brightPixmap);}
            }
        }
    }
    QPixmap currentPixmap;
    // 绘制角色
    if(isMoving||isAutoMoving){
        currentPixmap = (currentDirection == Up) ? upAnimation[currentFrame] :
                            (currentDirection == Down) ? downAnimation[currentFrame] :
                            (currentDirection == Left) ? leftAnimation[currentFrame] : rightAnimation[currentFrame];}
    else{
        currentPixmap = (currentDirection == Up) ? upAnimation[0] :
                            (currentDirection == Down) ? downAnimation[0] :
                            (currentDirection == Left) ? leftAnimation[0] : rightAnimation[0];
    }

    // 计算角色的绘制位置，相对于视窗
    float interpolatedX = (1 - moveProgress) * playerX + moveProgress * targetX;
    float interpolatedY = (1 - moveProgress) * playerY + moveProgress * targetY;

    float playerDrawXf = (interpolatedX - viewportX) * gridSizeXf;
    float playerDrawYf = (interpolatedY - viewportY) * gridSizeYf;
    int playerDrawX = static_cast<int>(std::floor(playerDrawXf));
    int playerDrawY = static_cast<int>(std::floor(playerDrawYf));

    painter.drawPixmap(playerDrawX, playerDrawY, gridSizeX, gridSizeY, currentPixmap);
}


void MazeGame::keyPressEvent(QKeyEvent *event) {


    if (event->key() == Qt::Key_R) {
        if (isAutoMoving) {
            // 如果正在自动移动，按下R键则停止自动移动
            isAutoMoving = false;
            path.clear(); // 清除路径
        } else {
            // 如果未开启自动移动，按下R键则开始自动移动
            if(mazes[ID-1].isTaskMaze)
                path = AStarSearch(maze, playerX, playerY,mazes[ID-1].doors[0].locationX , mazes[ID-1].doors[0].locationY);
            else
                path = AStarSearch(maze, playerX, playerY, endX, endY);
            if (!path.empty()) {
                isAutoMoving = true;
                pathIndex = 1; // 从路径的第二个节点开始（第一个是当前玩家位置）
                startMoving(path[pathIndex].first, path[pathIndex].second);
            }
        }
        return;
    }

    if (isAutoMoving) {
        return; // 如果正在自动移动，忽略手动输入
    }
    else if (isMoving) {
        return; // 如果正在移动，不允许新的移动
    }

    // 处理手动移动的代码
    int newX = playerX, newY = playerY;

    if (event->key() == Qt::Key_W || event->key() == Qt::Key_Up) {
        newY--;
        currentDirection = Up;
        if (newX >= 0 && newX < width && newY >= 0 && newY < length && maze[newY][newX] != 0) {
            startMoving(newX, newY);
        }
    } else if (event->key() == Qt::Key_S || event->key() == Qt::Key_Down) {
        newY++;
        currentDirection = Down;
        if (newX >= 0 && newX < width && newY >= 0 && newY < length && maze[newY][newX] != 0) {
            startMoving(newX, newY);
        }
    } else if (event->key() == Qt::Key_A || event->key() == Qt::Key_Left) {
        newX--;
        currentDirection = Left;
        if (newX >= 0 && newX < width && newY >= 0 && newY < length && maze[newY][newX] != 0) {
            startMoving(newX, newY);
        }
    } else if (event->key() == Qt::Key_D || event->key() == Qt::Key_Right) {
        newX++;
        currentDirection = Right;
        if (newX >= 0 && newX < width && newY >= 0 && newY < length && maze[newY][newX] != 0) {
            startMoving(newX, newY);
        }
    }else if ((event->key() == Qt::Key_E) && (maze[playerY][playerX] == 10)) {
        printf("update success?");
        for (int i = 0; i < mazes[ID-1].doors.size(); i++) {
            if (mazes[ID-1].doors[i].locationX == playerX && mazes[ID-1].doors[i].locationY == playerY) {
                printf("update success?!!!!");
                int old_ID = ID;
                ID = mazes[ID-1].doors[i].towardMaze; // 切换到新的迷宫
                maze = mazes[ID-1].maze; // 更新当前迷宫
                printf("update success");
                // 在新迷宫中找到返回的门的位置
                for (int j = 0; j < mazes[ID-1].doors.size(); j++) {
                    if (mazes[ID-1].doors[j].towardMaze == old_ID) {
                        playerX = mazes[ID-1].doors[j].locationX; // 设置玩家新的位置
                        playerY = mazes[ID-1].doors[j].locationY;
                        break; // 找到返回门后立即退出内层循环
                    }
                }
                break; // 找到当前门后立即退出外层循环
            }
        }
        updateViewport();
        update();
    }
    else if((event->key() == Qt::Key_E) && (maze[playerY][playerX] == 2)){
        playerX=1;
        playerY=1;
        generateMaze();
        setFurthestEndPoint();
        layers++;
    }


    // 检查新位置是否可移动（例如，不是墙）


}


void MazeGame::loadSave(int playerX, int playerY, int endX, int endY, std::vector<Maze> mazes,int ID,int layers) {
    this->mazes = mazes;
    this->playerX = playerX;
    this->playerY = playerY;
    this->endX = endX;
    this->endY = endY;
    this->ID=ID;
    this->layers=layers;
    this->maze=mazes[ID-1].maze;
    updateViewport();
}

void MazeGame::startMoving(int newX, int newY) {
    // 根据目标位置与当前位置的差值，设置角色朝向
    if (newX > playerX) {
        currentDirection = Right;
    } else if (newX < playerX) {
        currentDirection = Left;
    } else if (newY > playerY) {
        currentDirection = Down;
    } else if (newY < playerY) {
        currentDirection = Up;
    }

    isMoving = true;
    moveProgress = 0.0f;
    targetX = newX;
    targetY = newY;
    timer->start(16); // 大约60帧每秒
}


void MazeGame::updateAnimation() {
    moveProgress += 0.05f; // 调整步长控制移动速度
    if (moveProgress >= 1.0f) {
        moveProgress = 1.0f;
        playerX = targetX;
        playerY = targetY;
        isMoving = false;
        timer->stop();

        if (isAutoMoving) {
            pathIndex++;
            if (pathIndex < path.size()) {
                // 继续移动到下一个节点
                startMoving(path[pathIndex].first, path[pathIndex].second);
            } else {
                // 已经到达终点，停止自动移动
                isAutoMoving = false;
                path.clear();
            }
        }
    }

    // 更新动画帧计数器
    animationCounter++;
    if (animationCounter >= 6) { // 每6次更新（约100ms）更新一次动画帧
        animationCounter = 0;
        currentFrame = (currentFrame + 1) % 3;
    }

    // 更新视窗位置
    updateViewport();

    // 重绘窗口
    update();
}



void MazeGame::generateMaze() {
    MazeGenerator Maze1(width, length, seeds,mode,isAllowNesting);
    printf("hallo");
    mazes=Maze1.generateMazes();
    printf("hallo");
    maze=mazes[0].maze;
    ID=1;
}

void MazeGame::setFurthestEndPoint() {
    int startX = playerX, startY = playerY;
    endX = startX;
    endY = startY;
    int maxDistance = 0;

    for (int y = 1; y < length; y += 2) {
        for (int x = 1; x < width; x += 2) {
            if (maze[y][x] == 1) { // 可通行的路径
                int distance = abs(x - startX) + abs(y - startY); // 曼哈顿距离
                if (distance > maxDistance) {
                    maxDistance = distance;
                    endX = x;
                    endY = y;
                }
            }
        }
    }

    maze[endY][endX] = 2; // 标记终点
    mazes[0].maze=maze;
}

void MazeGame::saveAndQuit() {
    // 保存当前游戏状态
    Save saveGame(length, width, seeds, mode, mazes, playerX, playerY, endX, endY,ID,layers);
    saveGame.saveToFile();

    // 返回到主菜单
    this->close();
    MainWindow *menu = new MainWindow();
    menu->setAttribute(Qt::WA_DeleteOnClose);
    menu->show();
}

QPixmap MazeGame::adjustBrightness(const QPixmap &pixmap, float brightnessFactor, int row, int col,std::vector<std::pair<int,int>> lightblock1) {
    QImage image = pixmap.toImage();

    // 获取光源的亮度
    float brightnessFactorFinal = brightnessFactor;

    // 检查是否在光源范围内
    std::vector<std::pair<int, int>> lightblock = lightblock1; // 获取光源列表，方法可以自行实现
    for (const auto &light : lightblock) {
        int lightX = light.second;
        int lightY = light.first;
        float dist = calculateLightDistance(lightX, lightY, col, row);

        // 如果距离小于最大光照范围，计算亮度
        /* if (dist < maxLightDistance) {
            brightnessFactorFinal = maxBrightness / (1.0f + dist * dist * attenuation);
        } else {
            brightnessFactorFinal = 0.1f;  // 如果超出范围，暗淡*/
        if (dist < 16) {
            brightnessFactorFinal = 1.0f / (1.0f + dist * dist * 0.1);
        } else {
            brightnessFactorFinal = 0.1f;  // 如果超出范围，暗淡
        }
    }

    // 修改图像亮度
    for (int y = 0; y < image.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(image.scanLine(y));
        for (int x = 0; x < image.width(); ++x) {
            QColor color = QColor::fromRgb(line[x]);
            int red = qBound(0, static_cast<int>(color.red() * brightnessFactorFinal), 255);
            int green = qBound(0, static_cast<int>(color.green() * brightnessFactorFinal), 255);
            int blue = qBound(0, static_cast<int>(color.blue() * brightnessFactorFinal), 255);
            line[x] = QColor(red, green, blue).rgba();
        }
    }

    return QPixmap::fromImage(image);
}

float MazeGame::calculateLightDistance(int startX, int startY, int targetX, int targetY) {
    // 计算从 (startX, startY) 到 (targetX, targetY) 的直线距离
    float dx = targetX - startX;
    float dy = targetY - startY;
    int steps = std::max(std::abs(dx), std::abs(dy));

    // 每一步检查是否有墙壁
    float distance = 0.0f;
    for (int i = 0; i < steps; ++i) {
        int x = startX + i * dx / steps;
        int y = startY + i * dy / steps;

        if (maze[y][x] == 0) {  // 如果是墙壁，阻挡光线
            return INFINITY;  // 返回一个非常大的值，表示光线被阻挡
        }

        // 计算光线经过的距离
        distance += std::sqrt(dx * dx + dy * dy) / steps;
    }

    return distance;
}

QPixmap MazeGame::adjustBrightness_DAY(const QPixmap &pixmap, float brightnessFactor) {
    QImage image = pixmap.toImage();

    for (int y = 0; y < image.height(); ++y) {
        QRgb *line = reinterpret_cast<QRgb *>(image.scanLine(y));
        for (int x = 0; x < image.width(); ++x) {
            QColor color = QColor::fromRgb(line[x]);
            int red = qBound(0, static_cast<int>(color.red() * brightnessFactor), 255);
            int green = qBound(0, static_cast<int>(color.green() * brightnessFactor), 255);
            int blue = qBound(0, static_cast<int>(color.blue() * brightnessFactor), 255);
            line[x] = QColor(red, green, blue).rgba();
        }
    }

    return QPixmap::fromImage(image);
}
