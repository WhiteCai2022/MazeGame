/********************************************************************************
** Form generated from reading UI file 'mapgenerateoptions.ui'
**
** Created by: Qt User Interface Compiler version 6.7.2
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_MAPGENERATEOPTIONS_H
#define UI_MAPGENERATEOPTIONS_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QComboBox>
#include <QtWidgets/QLabel>
#include <QtWidgets/QLineEdit>
#include <QtWidgets/QPushButton>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_MapGenerateOptions
{
public:
    QLabel *modeLabel;
    QPushButton *modeButton;
    QLabel *labelX;
    QLineEdit *lineEdit;
    QLabel *labelY;
    QLineEdit *lineEdit_2;
    QLabel *labelSeeds;
    QLineEdit *lineEdit_3;
    QPushButton *pushButton;
    QPushButton *pushButton_2;
    QComboBox *Nest;
    QLabel *label;

    void setupUi(QWidget *MapGenerateOptions)
    {
        if (MapGenerateOptions->objectName().isEmpty())
            MapGenerateOptions->setObjectName("MapGenerateOptions");
        MapGenerateOptions->resize(862, 630);
        MapGenerateOptions->setMaximumSize(QSize(862, 630));
        modeLabel = new QLabel(MapGenerateOptions);
        modeLabel->setObjectName("modeLabel");
        modeLabel->setGeometry(QRect(410, 150, 240, 20));
        modeLabel->setAlignment(Qt::AlignmentFlag::AlignCenter);
        modeButton = new QPushButton(MapGenerateOptions);
        modeButton->setObjectName("modeButton");
        modeButton->setGeometry(QRect(480, 180, 100, 40));
        labelX = new QLabel(MapGenerateOptions);
        labelX->setObjectName("labelX");
        labelX->setGeometry(QRect(280, 250, 30, 30));
        lineEdit = new QLineEdit(MapGenerateOptions);
        lineEdit->setObjectName("lineEdit");
        lineEdit->setGeometry(QRect(320, 250, 100, 30));
        labelY = new QLabel(MapGenerateOptions);
        labelY->setObjectName("labelY");
        labelY->setGeometry(QRect(440, 250, 30, 30));
        lineEdit_2 = new QLineEdit(MapGenerateOptions);
        lineEdit_2->setObjectName("lineEdit_2");
        lineEdit_2->setGeometry(QRect(480, 250, 100, 30));
        labelSeeds = new QLabel(MapGenerateOptions);
        labelSeeds->setObjectName("labelSeeds");
        labelSeeds->setGeometry(QRect(280, 310, 60, 30));
        lineEdit_3 = new QLineEdit(MapGenerateOptions);
        lineEdit_3->setObjectName("lineEdit_3");
        lineEdit_3->setGeometry(QRect(350, 310, 230, 30));
        pushButton = new QPushButton(MapGenerateOptions);
        pushButton->setObjectName("pushButton");
        pushButton->setGeometry(QRect(210, 370, 181, 51));
        pushButton_2 = new QPushButton(MapGenerateOptions);
        pushButton_2->setObjectName("pushButton_2");
        pushButton_2->setGeometry(QRect(430, 370, 181, 51));
        Nest = new QComboBox(MapGenerateOptions);
        Nest->addItem(QString());
        Nest->addItem(QString());
        Nest->setObjectName("Nest");
        Nest->setGeometry(QRect(310, 180, 91, 41));
        label = new QLabel(MapGenerateOptions);
        label->setObjectName("label");
        label->setGeometry(QRect(310, 150, 141, 31));

        retranslateUi(MapGenerateOptions);

        QMetaObject::connectSlotsByName(MapGenerateOptions);
    } // setupUi

    void retranslateUi(QWidget *MapGenerateOptions)
    {
        MapGenerateOptions->setWindowTitle(QCoreApplication::translate("MapGenerateOptions", "Map Generate Options", nullptr));
        modeLabel->setText(QCoreApplication::translate("MapGenerateOptions", "\350\257\267\351\200\211\346\213\251\346\270\270\346\210\217\346\250\241\345\274\217", nullptr));
        modeButton->setText(QCoreApplication::translate("MapGenerateOptions", "\346\250\241\345\274\217: 1", nullptr));
        labelX->setText(QCoreApplication::translate("MapGenerateOptions", "X:", nullptr));
        lineEdit->setPlaceholderText(QCoreApplication::translate("MapGenerateOptions", "\345\256\275\345\272\246 (\351\273\230\350\256\244 20)", nullptr));
        labelY->setText(QCoreApplication::translate("MapGenerateOptions", "Y:", nullptr));
        lineEdit_2->setPlaceholderText(QCoreApplication::translate("MapGenerateOptions", "\351\225\277\345\272\246 (\351\273\230\350\256\244 20)", nullptr));
        labelSeeds->setText(QCoreApplication::translate("MapGenerateOptions", "\347\247\215\345\255\220:", nullptr));
        lineEdit_3->setPlaceholderText(QCoreApplication::translate("MapGenerateOptions", "\351\232\217\346\234\272\347\247\215\345\255\220 (\351\273\230\350\256\244\345\275\223\345\211\215\346\227\266\351\227\264)", nullptr));
        pushButton->setText(QCoreApplication::translate("MapGenerateOptions", "\345\274\200\345\247\213\346\270\270\346\210\217", nullptr));
        pushButton_2->setText(QCoreApplication::translate("MapGenerateOptions", "\350\277\224\345\233\236", nullptr));
        Nest->setItemText(0, QCoreApplication::translate("MapGenerateOptions", "\346\230\257", nullptr));
        Nest->setItemText(1, QCoreApplication::translate("MapGenerateOptions", "\345\220\246", nullptr));

        label->setText(QCoreApplication::translate("MapGenerateOptions", "\350\277\267\345\256\253\346\230\257\345\220\246\345\205\201\350\256\270\345\265\214\345\245\227", nullptr));
    } // retranslateUi

};

namespace Ui {
    class MapGenerateOptions: public Ui_MapGenerateOptions {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_MAPGENERATEOPTIONS_H
