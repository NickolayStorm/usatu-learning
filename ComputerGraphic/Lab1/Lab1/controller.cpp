#include "controller.h"
#include <cmath>
#include <QDebug>
#include <QApplication>


Controller* Controller::_self = nullptr;
MainWindow* Controller::_mainWindow = nullptr;

Controller::Controller()
{
    _alpha = 45;
    _point = Point(90, 100, 90);
}

Controller* Controller::instance(){
    if(_self == nullptr){
        _self = new Controller();
    }
    return _self;
}

int Controller::init(int argc, char *argv[]){
    QApplication a(argc, argv);
    Controller::instance();
    Controller::_mainWindow = new MainWindow();
    _mainWindow->show();
    return a.exec();
}

QHash<QString, QLine> Controller::coordinateAxes(Length length){
    QLine x;
    QLine y;
    QLine z;

    int size = length;

    //z
    z.setP1(QPoint(0, size));
    z.setP2(QPoint(0, -size));

    //x
    x.setP1(QPoint( -size, 0));
    x.setP2(QPoint(size, 0));


    //z
    y.setP1(QPoint(size * cos(_alpha * M_PI/180), -size * sin(_alpha * M_PI/180)));
    y.setP2(QPoint(-size * cos(_alpha * M_PI/180), size * sin(_alpha * M_PI/180)));

    QHash<QString, QLine> axes = {
                                {"X", x},
                                {"Y", y},
                                {"Z", z}
                            };
    return axes;
}


QHash<QString, QPoint> Controller::complexDravingPoints(){
    QPoint tx, ty1, ty2, tz, t1, t2, t3;


    tx = QPoint(- _point.x(), 0);

    tz = QPoint(0, _point.z());

    ty1 = QPoint(_point.y(), 0);
    ty2 = QPoint(0, -_point.y());

    t1 = QPoint(tx.x(), ty2.y());
    t2 = QPoint(tx.x(), tz.y());
    t3 = QPoint(ty1.x(), tz.y());

    QHash<QString, QPoint> points = {
        {"T1", t1},
        {"T2", t2},
        {"T3", t3},
        {"Tx", tx},
        {"Tz", tz},
        {"Ty1", ty1},
        {"Ty2", ty2}
    };
    return points;
}


QHash<QString, QPoint> Controller::dimensionalDravingPoints(){
    QPoint tx, ty, tz, xy, yz, xz;

    tx = QPoint(0,0);
    ty = QPoint(0,0);
    tz = QPoint(0,0);
    xz = QPoint(0,0);
    yz = QPoint(0,0);
    xy = QPoint(0,0);

    tx = QPoint(- _point.x(), 0);
    tz = QPoint(0, _point.z());
    ty = QPoint(
                _point.y() * cos(_alpha * M_PI/180),
               -_point.y() * sin(_alpha * M_PI/180)
                );

    xz = QPoint(-_point.x(), _point.z());

    yz = QPoint(
                _point.y() * cos(_alpha * M_PI/180),
                _point.z() - _point.y() * sin(_alpha * M_PI/180)
                );
    xy = QPoint(
                - (_point.x() - _point.y() * cos(_alpha * M_PI/180)),
                -_point.y() * sin(_alpha * M_PI/180)
                );

    QHash<QString, QPoint> points = {
        {"Tx", tx},
        {"Ty", ty},
        {"Tz", tz},
        {"Txy", xy},
        {"Txz", xz},
        {"Tyz", yz}
    };

    return points;
}

void Controller::setAlpha(Angle alpha){
    _alpha = alpha;
    _mainWindow->updateAll();

}

void Controller::setPoint(int x, int y, int z){
    _point = Point(x, y, z);
    _mainWindow->updateAll();
}

QPoint Controller::point(){
    int x = _point.x();
    int y = _point.y();
    int z = _point.z();

    x = (x) - y * cos(_alpha * M_PI/180);
    y = z - y * sin(_alpha * M_PI/180);

    return QPoint(-x, y);
}
