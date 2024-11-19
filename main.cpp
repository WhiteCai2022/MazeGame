#include "mainwindow.h"
#include <QApplication>
#include <QLocale>
#include <QTranslator>
#include <QFontDatabase>

int main(int argc, char *argv[])
{
    QApplication a(argc, argv);

    // 从资源文件加载字体
    int fontId = QFontDatabase::addApplicationFont("./font/Cubic_11.ttf");
    QTranslator translator;
    const QStringList uiLanguages = QLocale::system().uiLanguages();
    for (const QString &locale : uiLanguages) {
        const QString baseName = "Maze_" + QLocale(locale).name();
        if (translator.load(":/i18n/" + baseName)) {
            a.installTranslator(&translator);
            break;
        }
    }
    // 检查是否加载成功
    if (fontId == -1) {
        qWarning() << "字体加载失败，请检查路径或字体文件格式。";
    } else {
        // 获取字体族名称
        QStringList fontFamilies = QFontDatabase::applicationFontFamilies(fontId);
        if (!fontFamilies.isEmpty()) {
            // 设置应用程序字体
            QFont font(fontFamilies.at(0), 12);  // 字体大小可以自行调整
            QApplication::setFont(font);
        } else {
            qWarning() << "字体族为空，可能是字体文件损坏或格式不兼容。";
        }
    }

    MainWindow w;
    w.show();

    return a.exec();
}
