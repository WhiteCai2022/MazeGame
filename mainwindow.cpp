#include "mainwindow.h"
#include "./ui_mainwindow.h"
#include"mapgenerateoptions.h"
#include "MazeGame.h"
#include "save.h"
#include "saveinfowidget.h"
#include <QPropertyAnimation>
MainWindow::MainWindow(QWidget *parent)
    : QMainWindow(parent)
    , ui(new Ui::MainWindow)
    , saveInfoWidget(new SaveInfoWidget(this))
{
    ui->setupUi(this);
    saveInfoWidget->setInfo("这里显示最近存档信息");
    connect(ui->pushButton, &QPushButton::clicked, this, &MainWindow::startGame);
    connect(ui->pushButton_2, &QPushButton::clicked, this, &QApplication::quit);
    connect(ui->pushButton_3, &QPushButton::clicked, this, &MainWindow::continueGame);
    ui->pushButton->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");
    ui->pushButton_2->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");
    ui->pushButton_3->setStyleSheet("QPushButton { border: none; } QPushButton:hover { border: 2px solid black; }");
    ui->pushButton_3->installEventFilter(this);

    saveInfoWidget->setStyleSheet("QLabel { border: 2px solid black; padding: 5px; background-color: white; }");
}

bool MainWindow::eventFilter(QObject *obj, QEvent *event) {
    if (obj == ui->pushButton_3) {
        if (event->type() == QEvent::Enter) {
            Save save;
            save.loadFromFile();
            QString info = QString("地图大小: %1x%2\n种子: %3\n玩家位置: (%4, %5)\n第%6层")
                               .arg(save.getWidth()).arg(save.getLength())
                               .arg(save.getSeeds())
                               .arg(save.getPX()).arg(save.getPY())
                               .arg(save.getLayers());
            saveInfoWidget->setInfo(info);

            // 显示在按钮右侧的位置
            QPoint pos = ui->pushButton_3->mapToGlobal(QPoint(ui->pushButton_3->width(), 0));
            saveInfoWidget->move(pos);
            saveInfoWidget->show();
        } else if (event->type() == QEvent::Leave) {
            saveInfoWidget->hide();
        }
    }
    return QMainWindow::eventFilter(obj, event);
}

void MainWindow::startGame()
{
    MapGenerateOptions *mgo = new MapGenerateOptions;
    mgo->setAttribute(Qt::WA_DeleteOnClose);

    QPropertyAnimation *animation = new QPropertyAnimation(mgo, "windowOpacity");
    animation->setDuration(100);
    animation->setStartValue(0);
    animation->setEndValue(1);
    animation->start();

    mgo->show();  // 显示新窗口并启动动画
    this->hide();
}

void MainWindow::continueGame()
{
    Save save;
    save.loadFromFile();
    MazeGame *mazegame=new MazeGame(save.getWidth(),save.getLength(),save.getSeeds(),save.getMode(),false,1);
    mazegame->setAttribute(Qt::WA_DeleteOnClose);
    mazegame->loadSave(save.getPX(),save.getPY(),save.getEndX(),save.getEndY(),save.getMazes(),save.getID(),save.getLayers());
    this->close();
    mazegame->show();
    saveInfoWidget->close();
}

MainWindow::~MainWindow()
{

    delete ui;
}

