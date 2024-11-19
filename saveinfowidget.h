#ifndef SAVEINFOWIDGET_H
#define SAVEINFOWIDGET_H

#include <QWidget>

class SaveInfoWidget : public QWidget {
    Q_OBJECT
public:
    explicit SaveInfoWidget(QWidget *parent = nullptr);  // 声明构造函数
    void setInfo(const QString &info);
};

#endif // SAVEINFOWIDGET_H
