#ifndef COMPLEX_H
#define COMPLEX_H
#include <QWidget>
#include <QPainter>
#include <QHash>
#include <QPoint>
#include "mainwindow.h"

class ComplexDrawing : public QWidget
{
    Q_OBJECT

    QHash<QString, QPoint> _points;

public:
    explicit ComplexDrawing(MainWindow*);
    void paintEvent(QPaintEvent*);
    void translateToNativeCoords(QPoint& p);
    void translateToNativeCoords(QLine& l);


signals:

public slots:
    void updateElems();
};

#endif // COMPLEX_H
