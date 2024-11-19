#include "mapgenerateoptions.h"
#include "ui_mapgenerateoptions.h"
#include "MazeGame.h"
#include "mainwindow.h"
#include <QPropertyAnimation>
#include <iostream>

MapGenerateOptions::MapGenerateOptions(QWidget *parent)
    : QWidget(parent)
    , ui(new Ui::MapGenerateOptions)
    , mapinfo()
    , gifPath("./gif/DFS.gif")
    , currentMode(0)  // 初始化模式为0
{
    ui->setupUi(this);
    setMouseTracking(true); // 开启鼠标追踪

    connect(ui->pushButton, &QPushButton::clicked, this, &MapGenerateOptions::StartGame);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &MapGenerateOptions::BackToMenu);
    connect(ui->modeButton, &QPushButton::clicked, this, &MapGenerateOptions::toggleMode);

    // 设置按钮的样式
    ui->pushButton->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");
    ui->modeButton->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");

    // 设置提示文本
    ui->lineEdit->setPlaceholderText("请输入地图宽度 (默认 20)");
    ui->lineEdit_2->setPlaceholderText("请输入地图长度 (默认 20)");
    ui->lineEdit_3->setPlaceholderText("请输入种子 (默认当前时间)");

    // 设置模式按钮的初始文本
    ui->modeButton->setText("模式: DFS");

    // 创建提示窗口
    createTooltip();
}

MapGenerateOptions::~MapGenerateOptions()
{
    delete ui;
}

void MapGenerateOptions::toggleMode()
{
    // 假设有3种模式，循环切换
    currentMode = (currentMode + 1) % 3;
    switch (currentMode) {
    case 0:
        ui->modeButton->setText("模式: DFS");
        gifPath = "./gif/DFS.gif";
        break;
    case 1:
        ui->modeButton->setText("模式: Kruskal");
        gifPath = "./gif/Kruskal.gif";
        break;
    case 2:
        ui->modeButton->setText("模式: Prim");
        gifPath = "./gif/PRIM.gif";
        break;
    }
    //创建新的 QMovie 对象并应用到 tooltip 上
    QMovie *movie = new QMovie(gifPath);
    tooltip->setMovie(movie);
    // 设置动图的合适大小，确保按比例缩小
    movie->setScaledSize(QSize(350, 350)); // 动图缩小
    movie->start();
    // 设置边框
    tooltip->setStyleSheet("QLabel { border: 2px solid blue; background-color: white; }");
    tooltip->setVisible(false); // 初始时隐藏提示窗口
    // 删除旧的 QMovie 对象以释放资源
    if (tooltip->movie() != movie) {
        delete tooltip->movie();
    }
}


void MapGenerateOptions::SaveWhenButtonClicked()
{
    mapinfo.setWidth(ui->lineEdit->text().isEmpty() ? 20 : ui->lineEdit->text().toInt());
    mapinfo.setLength(ui->lineEdit_2->text().isEmpty() ? 20 : ui->lineEdit_2->text().toInt());
    mapinfo.setSeeds(ui->lineEdit_3->text().isEmpty() ? time(0) : ui->lineEdit_3->text().toInt());
    mapinfo.setMode(currentMode); // 更新 mapinfo 的模式
    mapinfo.setNest(ui->Nest->currentText()=="是"?true:false);

}

MapInfo MapGenerateOptions::getMapInfo()
{
    return mapinfo;
}

void MapGenerateOptions::StartGame()
{
    this->SaveWhenButtonClicked();
    MazeGame *window = new MazeGame(this->getMapInfo().getWidth(),
                                    this->getMapInfo().getLength(),
                                    this->getMapInfo().getSeeds(),
                                    this->getMapInfo().getMode(),
                                    this->getMapInfo().getNest(),
                                                                1);
    window->setAttribute(Qt::WA_DeleteOnClose);
    window->show();  // 显示游戏窗口
    this->close();
}

void MapGenerateOptions::BackToMenu()
{
    this->close();
    MainWindow *menu = new MainWindow();
    menu->setAttribute(Qt::WA_DeleteOnClose);
    QPropertyAnimation *animation = new QPropertyAnimation(menu, "windowOpacity");
    animation->setDuration(100);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();
    menu->show();
    this->close();
}

void MapGenerateOptions::createTooltip()
{
    tooltip = new QLabel(this);
    tooltip->setAttribute(Qt::WA_TransparentForMouseEvents);
    tooltip->setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    //创建新的 QMovie 对象并应用到 tooltip 上
    QMovie *movie = new QMovie(gifPath);
    tooltip->setMovie(movie);
    // 设置动图的合适大小，确保按比例缩小
    movie->setScaledSize(QSize(350, 350)); // 动图缩小
    movie->start();
    // 设置边框
    tooltip->setStyleSheet("QLabel { border: 2px solid blue; background-color: white; }");
    tooltip->setVisible(false); // 初始时隐藏提示窗口
    // 删除旧的 QMovie 对象以释放资源
    if (tooltip->movie() != movie) {
        delete tooltip->movie();
    }


}


void MapGenerateOptions::showTooltip(const QPoint &pos)
{
    tooltip->move(pos.x() + 10, pos.y() + 10); // 在鼠标位置稍微偏移显示
    tooltip->setVisible(true);
}

void MapGenerateOptions::hideTooltip()
{
    tooltip->setVisible(false);
}

void MapGenerateOptions::enterEvent(QEnterEvent *event)
{
    QWidget::enterEvent(event); // 不需要显示提示
}

void MapGenerateOptions::leaveEvent(QEvent *event)
{
    hideTooltip();
    QWidget::leaveEvent(event);
}

void MapGenerateOptions::mouseMoveEvent(QMouseEvent *event)
{
    if (ui->modeButton->geometry().contains(mapFromGlobal(event->globalPosition().toPoint()))) {
        // 当鼠标移动到 modeButton 上时显示提示
        QPoint pos = ui->modeButton->mapToGlobal(ui->modeButton->rect().topRight());
        showTooltip(pos);
    } else {
        // 当鼠标离开 modeButton 时隐藏提示
        hideTooltip();
    }
}


