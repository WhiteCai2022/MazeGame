#ifndef MAINWINDOW_H
#define MAINWINDOW_H
#include <QMovie>
#include <QMainWindow>
#include <QStackedWidget>
#include "saveinfowidget.h"

QT_BEGIN_NAMESPACE
namespace Ui {
class MainWindow;
}
QT_END_NAMESPACE

class MainWindow : public QMainWindow
{
    Q_OBJECT


public:

    MainWindow(QWidget *parent = nullptr);
    ~MainWindow();
    bool eventFilter(QObject *obj, QEvent *event) override;

private slots:
    void startGame();
    void continueGame();


private:
    SaveInfoWidget * saveInfoWidget;
    Ui::MainWindow *ui;
};
#endif // MAINWINDOW_H
