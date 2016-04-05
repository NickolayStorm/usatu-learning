#include "mainwindow.h"
#include <QApplication>
#include <QGraphicsDropShadowEffect>
#include <authorization.h>
#include "selectgame.h"
#include "chat.h"
int main(int argc, char *argv[])
{
    QApplication a(argc, argv);
    //a.setStyleSheet();//"QMainWindow {background-color: #000033; opacity: 0.7;}");
    //MainWindow w(nullptr, QString("4"), QString("1"));
    //w.setStyleSheet();
    authorization w;
    //NiSelectGame w(nullptr, "3");
    //Chat w(nullptr, 0, "2", "3");
    w.show();

    return a.exec();
}
