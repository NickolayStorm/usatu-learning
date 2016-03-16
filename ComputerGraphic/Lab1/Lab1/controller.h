#ifndef CONTROLLER_H
#define CONTROLLER_H
#include <QHash>
#include <QString>
#include <QLine>
#include <QPoint>
#include "mainwindow.h"

using Length = int;
using Angle = int;

class Point{
    int _x;
    int _y;
    int _z;
public:
    Point(){}
    Point(int x, int y, int z):_x(x), _y(y), _z(z){}
    inline int x(){return _x;}
    inline int y(){return _y;}
    inline int z(){return _z;}


};

class Controller
{  
    Controller();
    Point _point;
    Angle _alpha;
    static Controller *_self;
    static MainWindow *_mainWindow;
public:
    static Controller* instance();
    static int init(int argc, char *argv[]);
    void setAlpha(Angle alpha);
    void setPoint(int x, int y, int z);
    QHash<QString, QLine> coordinateAxes(Length length);
    QPoint point();
    QHash<QString, QPoint> complexDravingPoints();
    QHash<QString, QPoint> dimensionalDravingPoints();
};

#endif // CONTROLLER_H
