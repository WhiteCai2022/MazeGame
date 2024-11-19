/********************************************************************************
** Form generated from reading UI file 'properties.ui'
**
** Created by: Qt User Interface Compiler version 6.7.3
**
** WARNING! All changes made in this file will be lost when recompiling UI file!
********************************************************************************/

#ifndef UI_PROPERTIES_H
#define UI_PROPERTIES_H

#include <QtCore/QVariant>
#include <QtWidgets/QApplication>
#include <QtWidgets/QWidget>

QT_BEGIN_NAMESPACE

class Ui_Properties
{
public:

    void setupUi(QWidget *Properties)
    {
        if (Properties->objectName().isEmpty())
            Properties->setObjectName("Properties");
        Properties->resize(400, 300);

        retranslateUi(Properties);

        QMetaObject::connectSlotsByName(Properties);
    } // setupUi

    void retranslateUi(QWidget *Properties)
    {
        Properties->setWindowTitle(QCoreApplication::translate("Properties", "Form", nullptr));
    } // retranslateUi

};

namespace Ui {
    class Properties: public Ui_Properties {};
} // namespace Ui

QT_END_NAMESPACE

#endif // UI_PROPERTIES_H
