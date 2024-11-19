#ifndef MAPGENERATEOPTIONS_H
#define MAPGENERATEOPTIONS_H

#include <QWidget>
#include <QLabel>
#include "mapinfo.h"
#include <QMouseEvent>


namespace Ui {
class MapGenerateOptions;
}

class MapGenerateOptions : public QWidget
{
    Q_OBJECT

public:
    explicit MapGenerateOptions(QWidget *parent = nullptr);
    ~MapGenerateOptions();
    void SaveWhenButtonClicked();
    MapInfo getMapInfo();

private slots:
    void BackToMenu();

private slots:
    void StartGame();
    void toggleMode();  // 切换模式函数

protected:
    void enterEvent(QEnterEvent *event) override; // 鼠标进入事件
    void leaveEvent(QEvent *event) override; // 鼠标离开事件
    void mouseMoveEvent(QMouseEvent *event) override;

private:
    QLabel *tooltip; // 用于显示提示的 QLabel
    void createTooltip(); // 创建提示窗口
    void showTooltip(const QPoint &pos); // 显示提示窗口
    void hideTooltip(); // 隐藏提示窗口
    int currentMode;// 当前模式
    Ui::MapGenerateOptions *ui;
    MapInfo mapinfo;
    QString gifPath;
    bool isAllowNesting;
};




#endif // MAPGENERATEOPTIONS_H
