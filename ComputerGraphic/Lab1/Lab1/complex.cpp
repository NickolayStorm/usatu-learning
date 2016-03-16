#include "complex.h"
#include "controller.h"
#include <QFont>

ComplexDrawing::ComplexDrawing(MainWindow *parent) : QWidget(parent)
{
    this->updateElems();
    connect(parent, SIGNAL(updateElems()), this, SLOT(updateElems()));

}

void ComplexDrawing::updateElems(){
    _points = Controller::instance()->complexDravingPoints();
    for(auto&x : _points){
        this->translateToNativeCoords(x);
    }
    update();
}

void ComplexDrawing::paintEvent(QPaintEvent *){
    QPainter paint(this);
    QPen pen;
    QBrush brush(QColor(135,206,235, 255));
    paint.setBrush(brush);
    pen.setColor(QColor(20,10,70,255));
    paint.drawRect(0,0,this->width(),this->height());

    int size = this->width() / 2 - 20;
    QLine x, y;
    //y
    y.setP1(QPoint(0, size));
    y.setP2(QPoint(0, -size));

    //x
    x.setP1(QPoint( -size, 0));
    x.setP2(QPoint(size, 0));

    this->translateToNativeCoords(x);
    this->translateToNativeCoords(y);

    paint.drawLine(x);
    paint.drawLine(y);
    paint.drawText(y.p1(), "Z");
    paint.drawText(x.p1(), "X");
    paint.drawText(x.p2(), "Y");
    paint.drawText(y.p2(), "Y");

    QPoint t1 = _points.value("T1");
    //paint.drawText(t1, "T1");

    QPoint t2 = _points.value("T2");
    //paint.drawText(t2, "T2");

    QPoint t3 = _points.value("T3");
    //paint.drawText(t3, "T3");

    QLine line(t1, t2);
    paint.drawLine(line);

    line.setPoints(t2,t3);
    paint.drawLine(line);

    QPoint zero(0,0);
    this->translateToNativeCoords(zero);
    paint.drawEllipse(zero, 1, 1);

    QPoint ty1 = _points.value("Ty1");
    QPoint ty2 = _points.value("Ty2");

    QSize area((ty1.x() - zero.x())*2, (ty2.y() - zero.y())*2);

    int delta = ty1.x() - zero.x();

    QPoint areaPoint(zero.x() - delta, zero.y() - delta);

    int startAngle = zero.x() > ty1.x() ? 90*16 : 0;
    int spainAngle = zero.x() > ty1.x() ? 90*16 : -90*16;

    paint.drawArc(QRect(areaPoint, area), startAngle, spainAngle);

    zero += QPoint(10, -10);
    paint.drawText(zero, "0");

    pen.setStyle(Qt::DashLine);
    paint.setPen(pen);

    paint.drawLine(t1, ty2);
    paint.drawLine(t3, ty1);

    QPoint tx = _points.value("Tx");
    QPoint tz = _points.value("Tz");
    line.setPoints(t3, tz);
    paint.drawLine(line);

    line.setPoints(t1, tx);
    paint.drawLine(line);

    line.setPoints(t2, tx);
    paint.drawLine(line);
    QFont font;
    font.setPointSize(9);
    paint.setFont(font);
    font.setFamily("Arial");
    QPoint p;
    for(auto &k : _points.keys()){
        p = _points.value(k);
        paint.drawText(p, k);
    }

    brush.setColor(Qt::blue);
    paint.setBrush(brush);
    pen.setColor(Qt::blue);
    paint.setPen(pen);
    for(auto&p : _points){
        paint.drawEllipse(p, 2, 2);
    }

    brush.setColor(Qt::darkBlue);
    paint.setBrush(brush);
    pen.setColor(Qt::darkBlue);
    paint.setPen(pen);

    paint.drawEllipse(t1, 3, 3);
    paint.drawEllipse(t2, 3, 3);
    paint.drawEllipse(t3, 3, 3);

}

void ComplexDrawing::translateToNativeCoords(QLine& l){

    //swap y's
    QPoint p1 = l.p1();
    QPoint p2 = l.p2();

    auto tempY = p1.y();

    p1.setY(p2.y());
    p2.setY(tempY);

    l.setPoints(p1, p2);
    l.translate(this->width() / 2, this->height() / 2);
}

void ComplexDrawing::translateToNativeCoords(QPoint &p){
    p.setY(-p.y());
    p += QPoint(this->width() / 2, this->height() / 2);
}
