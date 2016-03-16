#include "dimensional.h"
#include <QLine>
#include <controller.h>
#include <QDebug>

DimensionalDrawing::DimensionalDrawing(MainWindow *parent) : QWidget(parent)
{
    _coordinateAxes = Controller::instance()->coordinateAxes(354 / 2 - 20);
    _point = Controller::instance()->point();
    _helperPoints = Controller::instance()->dimensionalDravingPoints();

    for(auto&p : _helperPoints){
        this->translateToNativeCoords(p);
    }

    connect(parent, SIGNAL(updateElems()), this, SLOT(updateElems()));
}

void DimensionalDrawing::paintEvent(QPaintEvent *){
    QPainter paint(this);

    QFont font;
    font.setFamily("Arial");
    font.setPointSize(11);
    paint.setFont(font);

    QPen pen;
    QBrush brush(QColor(255,245,173, 255));
    paint.setBrush(brush);
    paint.drawRect(0,0,this->width(),this->height());

    pen.setColor(QColor(0,0,0,255));
    paint.setPen(pen);

    //x
    QLine x = _coordinateAxes.value("X");
    this->translateToNativeCoords(x);
    paint.drawLine(x);
    paint.drawText(x.p1(), "X");


    //y
    QLine y = _coordinateAxes.value("Y");
    this->translateToNativeCoords(y);
    paint.drawLine(y);
    paint.drawText(y.p1(), "Y");

    //z
    QLine z = _coordinateAxes.value("Z");
    this->translateToNativeCoords(z);
    paint.drawLine(z);
    paint.drawText(z.p1(), "Z");

    //T
    QPoint t = _point;
    this->translateToNativeCoords(t);

    paint.drawText(t, "T");

    //Zero
    QPoint zero(0,0);
    this->translateToNativeCoords(zero);
    paint.drawEllipse(zero, 2, 2);
    zero += QPoint(10, -10);
    paint.drawText(zero, "0");

    pen.setColor(Qt::blue);
    brush.setColor(Qt::blue);
    paint.setPen(pen);
    paint.setBrush(brush);
    QPoint tx, ty, tz, xy, xz, yz;
    tx = _helperPoints.value("Tx");
    ty = _helperPoints.value("Ty");
    tz = _helperPoints.value("Tz");

    xy = _helperPoints.value("Txy");
    xz = _helperPoints.value("Txz");
    yz = _helperPoints.value("Tyz");

    for(auto&p : _helperPoints){
        paint.drawEllipse(p, 2, 2);
    }

    brush.setColor(Qt::black);
    paint.setPen(pen);
    paint.setBrush(brush);

    font.setPointSize(9);
    paint.setFont(font);

    QPoint p;
    for(auto &k : _helperPoints.keys()){
        p = _helperPoints.value(k);
        paint.drawText(p, k);
    }

    pen.setStyle(Qt::DashLine);
    pen.setColor(QColor(115, 117, 115, 255));
    paint.setPen(pen);

    paint.drawLine(t, xz);
    paint.drawLine(t, yz);
    paint.drawLine(t, xy);

    paint.drawLine(tx, xy);
    paint.drawLine(tx, xz);

    paint.drawLine(ty, yz);
    paint.drawLine(ty, xy);

    paint.drawLine(tz, xz);
    paint.drawLine(tz, yz);

    pen.setColor(Qt::darkBlue);
    brush.setColor(Qt::darkBlue);
    paint.setPen(pen);
    paint.setBrush(brush);
    paint.drawEllipse(t, 3, 3);

}

void DimensionalDrawing::translateToNativeCoords(QLine& l){

    //swap y's
    QPoint p1 = l.p1();
    QPoint p2 = l.p2();

    auto tempY = p1.y();

    p1.setY(p2.y());
    p2.setY(tempY);

    l.setPoints(p1, p2);
    l.translate(this->width() / 2, this->height() / 2);
}

void DimensionalDrawing::translateToNativeCoords(QPoint &p){
    p.setY(-p.y());
    p += QPoint(this->width() / 2, this->height() / 2);
}

void DimensionalDrawing::updateElems(){
    _coordinateAxes = Controller::instance()->coordinateAxes(this->width() / 2 - 20);
    _point = Controller::instance()->point();
    _helperPoints = Controller::instance()->dimensionalDravingPoints();

    for(auto&x : _helperPoints){
        this->translateToNativeCoords(x);
    }

    update();
    //And up to date point
}
