#include "SaveInfoWidget.h"
#include <QLabel>
#include <QVBoxLayout>

SaveInfoWidget::SaveInfoWidget(QWidget *parent) : QWidget(parent) {  // 定义构造函数
    setWindowFlags(Qt::ToolTip | Qt::FramelessWindowHint);
    QVBoxLayout *layout = new QVBoxLayout(this);
    QLabel *label = new QLabel(this);
    label->setAlignment(Qt::AlignCenter);
    layout->addWidget(label);
}

void SaveInfoWidget::setInfo(const QString &info) {
    QLabel *label = findChild<QLabel*>();
    if (label) {
        label->setText(info);
    }
}
