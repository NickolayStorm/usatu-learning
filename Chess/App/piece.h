#ifndef PIECE_H
#define PIECE_H
#include <QGraphicsPixmapItem>
#include <string>
#include <iostream>
#include <QMouseEvent>
using namespace std;
class Piece : public QGraphicsPixmapItem
{
    int _id;
    QPoint _posOnBoard;
public:
    //QPoint pos == position on board
    Piece(int id, QPoint pos, int globalPosX, int globalPosY, QPixmap &icon);
    void setBoardPos(QPoint pos){
        _posOnBoard = pos;
    }
    virtual void ping(){
        char c = 'a'+ _posOnBoard.x();
        cout << "id = " << who() << "\n" << ", (" << c << "-" << _posOnBoard.y() + 1<< ")" << endl;
    }


   // void move(int x, int y, int sizeOfCell);//
    //void mousePressEvent(QMouseEvent *e);
    void moveTo(QPoint p, QPoint global);

    int who(){
        return _id;
    }

    QPoint getBoardPos(){
        return _posOnBoard;
    }
    //string name(){
     //   return _pieseName;
    //}

    ~Piece();
};

#endif // PIECE_H
