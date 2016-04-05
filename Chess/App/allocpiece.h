#ifndef ALLOCPIECE_H
#define ALLOCPIECE_H
#include <QGraphicsPixmapItem>
#include <piece.h>

class AllocPiece : public QGraphicsPixmapItem
{
    Piece *alloc = nullptr;

public:    
    Piece* get(){
        return alloc;
    }

    void set(Piece* a){
        alloc = a;
    }

    AllocPiece(QPixmap &);
    ~AllocPiece();
};

#endif // ALLOCPIECE_H
