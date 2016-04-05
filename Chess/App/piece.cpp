#include "piece.h"

Piece::Piece(int id, QPoint pos, int globalPosX, int globalPosY, QPixmap &icon)
    : QGraphicsPixmapItem(icon)
{
    _id = id;
    _posOnBoard = pos;
    this->setPos(globalPosX, globalPosY);
}

//void Piece::mousePressEvent(QMouseEvent *e){
//    cout << "id = " << _id << "\n" << _pieseName << " " << _posOnBoard.x() << " " << _posOnBoard.y() << endl;
//}

void Piece::moveTo(QPoint p, QPoint global){
    _posOnBoard = p;
    this->setPos(global);
}



Piece::~Piece()
{

}

