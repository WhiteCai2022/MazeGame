/********************************************************************************
** Form generated from reading UI file 'mainwindow.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAINWINDOW_H
#define UI_MAINWINDOW_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QLabel>
#include <QtWidgets/QMainWindow>
#include <QtWidgets/QMenuBar>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QStatusBar>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MainWindow
{
public:
    QWidget *centralwidget;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QPushButton *pushButton_3;
    QLabel *backgroundLabel;
    QLabel *midgroundLabel;
    QLabel *foregroundLabel;
    QMenuBar *menubar;
    QStatusBar *statusbar;

    void setupUi(QMainWindow *MainWindow)
    {
        if (MainWindow->objectName().isEmpty())
            MainWindow->setObjectName("MainWindow");
        MainWindow->resize(807, 575);
        MainWindow->setMaximumSize(QSize(807, 575));
        centralwidget = new QWidget(MainWindow);
        centralwidget->setObjectName("centralwidget");
        pushButton = new QPushButton(centralwidget);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(300, 180, 181, 51));
        pushButton->setCheckable(false);
        pushButton->setAutoDefault(false);
        pushButton->setFlat(false);
        pushButton_2 = new QPushButton(centralwidget);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(300, 300, 181, 51));
        pushButton_3 = new QPushButton(centralwidget);
        pushButton_3->setObjectName("pushButton_3");
        pushButton_3->setGeometry(QRect(300, 240, 181, 51));
        pushButton_3->setCursor(QCursor(Qt::CursorShape::ArrowCursor));
        backgroundLabel = new QLabel(centralwidget);
        backgroundLabel->setObjectName("backgroundLabel");
        backgroundLabel->setGeometry(QRect(0, 20, 807, 575));
        midgroundLabel = new QLabel(centralwidget);
        midgroundLabel->setObjectName("midgroundLabel");
        midgroundLabel->setGeometry(QRect(0, 20, 807, 575));
        foregroundLabel = new QLabel(centralwidget);
        foregroundLabel->setObjectName("foregroundLabel");
        foregroundLabel->setGeometry(QRect(-50, 20, 807, 575));
        MainWindow->setCentralWidget(centralwidget);
        backgroundLabel->raise();
        foregroundLabel->raise();
        midgroundLabel->raise();
        pushButton_3->raise();
        pushButton_2->raise();
        pushButton->raise();
        menubar = new QMenuBar(MainWindow);
        menubar->setObjectName("menubar");
        menubar->setGeometry(QRect(0, 0, 807, 29));
        MainWindow->setMenuBar(menubar);
        statusbar = new QStatusBar(MainWindow);
        statusbar->setObjectName("statusbar");
        MainWindow->setStatusBar(statusbar);

        retranslateUi(MainWindow);
        QObject::connect(pushButton, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(pushButton_2, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));
        QObject::connect(pushButton_3, &QPushButton::clicked, MainWindow, qOverload<>(&QMainWindow::close));

        pushButton->setDefault(false);


        QMetaObject::connectSlotsByName(MainWindow);
    } // setupUi

    void retranslateUi(QMainWindow *MainWindow)
    {
        MainWindow->setWindowTitle(QCoreApplication::translate("MainWindow", "MainWindow", nullptr));
        pushButton->setText(QCoreApplication::translate("MainWindow", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MainWindow", "\351\200\200\345\207\272\346\270\270\346\210\217", nullptr));
        pushButton_3->setText(QCoreApplication::translate("MainWindow", "\347\273\247\347\273\255\346\270\270\346\210\217", nullptr));
        backgroundLabel->setText(QString());
        midgroundLabel->setText(QString());
        foregroundLabel->setText(QString());
    } // retranslateUi

};

namespace Ui {
    class MainWindow: public Ui_MainWindow {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAINWINDOW_H
