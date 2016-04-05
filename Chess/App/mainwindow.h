#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>
#include <QGraphicsScene>
#include <QMouseEvent>
#include <vector>
#include "piece.h"
#include <QLabel>
#include <QTimer>
#include "allocpiece.h"
#include "controlwidget.h"

#include <functional>
using namespace std;
//using std::tr1::function;
namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0,
                        QString id_game = "", QString id_player = "",
                        bool isWhite = true);

    void initLambds();
    void clearBoard();

    void clearImages();
    void updatePiece();
    void createBoard();
    void createPiece();

    void createHalfPieces(std::function<void (int&, QPoint&, int&, int&, QPixmap&)>& create, short begin, short end);
    //void createEnemyPiece(short begin, short end);

    void actionSceneHundler(QPoint &click);
    vector<QLabel*> labels_for_delete;
    void mousePressEvent(QMouseEvent *);
    void paintEvent(QPaintEvent*);
    bool movePiece(Piece*, QPointF newPos);
    ~MainWindow();
public slots:
    void checkUpdate();
private:
    //bool isAlloc = false;
    ControlWidget *controller;
    QTimer updateTimer;
    vector<QGraphicsItem*> pieces;
    vector<QGraphicsItem*> images;
    QString _id_player;
    QString _id_game;
    AllocPiece *alloc;
    Ui::MainWindow *ui;
    QGraphicsScene *scene;
    std::function<void (int&, QPoint&, int&, int&, QPixmap&)> genereJustImages;
    std::function<void (int&, QPoint&, int&, int&, QPixmap&)> genereTruthPieces;
    bool white = true;
    bool course = true;//его ли ход
};

#endif // MAINWINDOW_H
