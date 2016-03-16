#ifndef DIMENSIONAL_H
#define DIMENSIONAL_H
#include <QWidget>
#include <QPainter>
#include <QPen>
#include <QPoint>
#include <QHash>
#include <QLine>
#include "mainwindow.h"
class DimensionalDrawing : public QWidget
{
    Q_OBJECT

    QHash<QString, QLine> _coordinateAxes;
    QHash<QString, QPoint> _helperPoints;
    QPoint _point;

public:
    explicit DimensionalDrawing(MainWindow *parent = 0);
    void paintEvent(QPaintEvent *);
    void translateToNativeCoords(QLine& l);
    void translateToNativeCoords(QPoint& p);


signals:

public slots:
    void updateElems();
};

#endif // DIMENSIONAL_H
