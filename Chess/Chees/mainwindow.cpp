#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "database.h"
#include "controlwidget.h"
#include <QMessageBox>
#include <QTransform>
#include <iostream>
#include <functional>
using namespace std;

#define GRAPHIC_VIEW_POSITION_X 40
#define GRAPHIC_VIEW_POSITION_Y 30
#define SIZE_CELL 60
#define RIGHT_SHIFT 10
#define UPDATE_TIME 1000
#define UNALLOC_POS_TO_ALLOC_RECT -SIZE_CELL - 10,- SIZE_CELL -10

inline QPoint coordsToCellPoint(int x, int y){
    return QPoint(x/SIZE_CELL, y/SIZE_CELL);
}

inline QPoint cellPointToCoords(QPoint p){
    return QPoint(p.x()*SIZE_CELL, p.y()*SIZE_CELL);
}

MainWindow::MainWindow(QWidget *parent,
                       QString id_game, QString id_player,
                       bool isWhite) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)

{
    ui->setupUi(this);
    bool init = DataBase::initDB();
    if(true == init){
        initLambds();

        white = isWhite;
        _id_player = id_player;
        _id_game = id_game;

        controller = new ControlWidget(this, _id_game, _id_player);
        controller->setGeometry(550, GRAPHIC_VIEW_POSITION_X, controller->width(), controller->height());

        scene = new QGraphicsScene(this);
        scene->setSceneRect(0,0, SIZE_CELL * 8, SIZE_CELL * 8);
        ui->graphicsView->setScene(scene);
        createBoard();
        createPiece();
        ui->graphicsView->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff );
        ui->graphicsView->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOff );

        auto p = QPixmap(":/alloc01.png");
        alloc = new AllocPiece(p);
        alloc->setPos(UNALLOC_POS_TO_ALLOC_RECT);
        scene->addItem(alloc);
        setAttribute(Qt::WA_NoSystemBackground);
        this->setAttribute(Qt::WA_TranslucentBackground);

        bool isCourseWhites = DataBase::is_current(id_game);
        course = isCourseWhites ^ !white;//если ходят белые и мы белые, то наш ход

        connect(&updateTimer, SIGNAL(timeout()), this, SLOT(checkUpdate()));

        controller->setCursorText(course);
        if(course == false){
            updateTimer.start(UPDATE_TIME);
        }
        this->show();

    }else{
        QMessageBox::information(this, QString("Error"), QString("Ошибка соединения. Пожалуйста, проверьте своё подключение интернету!"));
        this->close();
    }
}

void MainWindow::createBoard(){
    bool isWhite = true;
    char count;
    count = white ? '8' : '1';
    short mv = white ? -1 : 1;// шаг для count
    labels_for_delete.reserve(24);
    for(int y = 0; y < SIZE_CELL*8; y += SIZE_CELL, count+=mv)
    {
        for(int x = 0; x < SIZE_CELL*8; x += SIZE_CELL)
        {
            QBrush brush;
            if(isWhite) brush = QBrush(QColor(255,255,255,100));
            else brush = QBrush(QColor(90,90,90,100));
            scene->addRect(x, y, SIZE_CELL, SIZE_CELL, QPen(Qt::black), brush);

            isWhite = !isWhite;
        }
        isWhite = !isWhite;
        QLabel *label = new QLabel(this);
        labels_for_delete.push_back(label);
        label->setText(QString(count));
        label->setGeometry(GRAPHIC_VIEW_POSITION_X - 10, y + GRAPHIC_VIEW_POSITION_Y + SIZE_CELL/2, 10,15);
    }

    count = white ? 'a' : 'h';
    mv = -mv;
    for(int x = 0; x < SIZE_CELL*8; x += SIZE_CELL, count+=mv){
        QLabel *label = new QLabel(this);
        labels_for_delete.push_back(label);
        label->setText(QString(count));
        label->setGeometry(GRAPHIC_VIEW_POSITION_X + x + SIZE_CELL/2,GRAPHIC_VIEW_POSITION_Y, 10,15);
        label = new QLabel(this);
        labels_for_delete.push_back(label);
        label->setText(QString(count));
        label->setGeometry(GRAPHIC_VIEW_POSITION_X + x + SIZE_CELL/2,GRAPHIC_VIEW_POSITION_Y+SIZE_CELL*8 + 20, 10,15);
    }
}

void MainWindow::initLambds(){

    genereJustImages = [&](int&, QPoint&, int& globalPosX, int& globalPosY, QPixmap& map){
                    QGraphicsPixmapItem *p = new QGraphicsPixmapItem(map);
                    p->setPos(globalPosX, globalPosY);
                    scene->addItem(p);
                    images.push_back(p);
    };

    genereTruthPieces = [&](int & currPieceId, QPoint& pos, int& globalPosX, int& globalPosY, QPixmap& map){
        Piece* p = new Piece(currPieceId, pos, globalPosX, globalPosY, map);
        scene->addItem(p);
        pieces.push_back(p);
    };
}

void MainWindow::createPiece(){  
    int startTruth;
    int endTruth;
    int startJust;
    int endJust;
    if(white){
        startTruth = 1;
        endTruth = 7;
        startJust = 7;
        endJust = 13;

     }else{
        startTruth = 7;
        endTruth = 13;
        startJust = 1;
        endJust = 7;
     }

    createHalfPieces(genereTruthPieces, startTruth, endTruth);
    createHalfPieces(genereJustImages, startJust, endJust);
}


void MainWindow::createHalfPieces(function <void
                                        (int&, QPoint&, int&, int&, QPixmap &)>
                                  &create,
                                  short begin, short end){
    QString dataNames[12];
    dataNames[0] =    "white_rook";
    dataNames[1] =    "white_knight";
    dataNames[2] =    "white_bishop";
    dataNames[3] =    "white_king";
    dataNames[4] =    "white_queen";
    dataNames[5] =    "white_pawn";
    dataNames[6] =    "black_rook";
    dataNames[7] =    "black_knight";
    dataNames[8] =    "black_bishop";
    dataNames[9] =    "black_queen";
    dataNames[10] =   "black_king";
    dataNames[11] =   "black_pawn";

    for(int currPieceId = begin; currPieceId < end; ++currPieceId){
        vector<int> pos_ah;
        vector<int> pos_18;
        pos_ah.reserve(8);
        pos_18.reserve(8);
        QString id_piece =  QString("%1").arg(currPieceId);
        bool ok = DataBase::get_positions_for_pieces(_id_game, id_piece, pos_ah, pos_18);
        if(ok){
            auto map = QPixmap(QString("://icons/") + dataNames[currPieceId - 1]);
            auto y = pos_18.begin();//Вынуждено, для цикла, не возвращать же точки ???
            for(int x : pos_ah){
                if(x != 0 && *y != 0){
                    int globalPosX;
                    int globalPosY;
                    QPoint pos;
                    if(white){
                        globalPosX = (7 - (x - 1)) * SIZE_CELL;
                        globalPosY = (7 - (*y - 1)) * SIZE_CELL;//POINT TO COORDS (inline) // MAYBE
                        pos = QPoint(7-x,7 - *y);
                    }else{
                        globalPosX = (x - 1) * SIZE_CELL;
                        globalPosY = (*y - 1) * SIZE_CELL;
                        pos  = QPoint(x, *y);
                    }
                    create(currPieceId, pos, globalPosX, globalPosY, map);
                }
                ++y;

            }
        }else{
            clearBoard();
            QMessageBox::information(this, QString("Error"), QString("Ошибка соединения. Пожалуйста, проверьте своё подключение интернету!"));
            break;
        }
    }
}

void MainWindow::clearImages(){
    for(auto x : images)
        scene->removeItem(x);
    images.clear();
}

void MainWindow::clearBoard(){
    auto scene = ui->graphicsView->scene();

    for(auto x : pieces)
        scene->removeItem(x);
    pieces.clear();

    clearImages();
}

void MainWindow::mousePressEvent(QMouseEvent *mouse){
    if(mouse->button() == Qt::LeftButton){
        QPoint pos = mouse->pos();
        cout << pos.x() << " " << pos.y()<< endl;
        if(pos.x() > GRAPHIC_VIEW_POSITION_X && pos.x() < ui->graphicsView->width() + GRAPHIC_VIEW_POSITION_X){
            if(pos.y() > GRAPHIC_VIEW_POSITION_Y && pos.y() < ui->graphicsView->height() + GRAPHIC_VIEW_POSITION_Y){
                actionSceneHundler(pos);
                return;
            }
        }
    }
}

void MainWindow::actionSceneHundler(QPoint &click){
    if(course == true){
        click -= QPoint(GRAPHIC_VIEW_POSITION_X, GRAPHIC_VIEW_POSITION_Y);//перевод в локальные координаты сцены
        auto p = scene->itemAt(click, QTransform());
        auto piece = dynamic_cast<Piece*>(p);
        if(piece){
            if(piece != alloc->get()){
                alloc->set(piece);
                alloc->setPos(alloc->get()->pos());
                piece->ping();
            }else{
                alloc->setPos(UNALLOC_POS_TO_ALLOC_RECT);
                alloc->set(nullptr);
            }
        }else{
            auto *allocPiece = alloc->get();
            if(allocPiece != nullptr){

                if(movePiece(allocPiece, click) == true){
                    course = false;
                    controller->setCursorText(false);
                    updateTimer.start(UPDATE_TIME);
                    alloc->setPos(UNALLOC_POS_TO_ALLOC_RECT);
                    alloc->set(nullptr);
                }
            }
        }
    }else QMessageBox::information(this, "Error", "Дождитесь своей очереди!");
}

bool MainWindow::movePiece(Piece *piece, QPointF newPos){
    QPoint npos = coordsToCellPoint(newPos.x(), newPos.y());
    QPoint ncoordspos = cellPointToCoords(npos);
    bool ok;
    if(white == true)
        ok = DataBase::move(_id_player, _id_game, piece->who(),
                         7 - piece->getBoardPos().x(), 7 - piece->getBoardPos().y(),
                         1+ 7 - npos.x(), 1 + 7 - npos.y());
    else
        ok = DataBase::move(_id_player, _id_game, piece->who(),
                             piece->getBoardPos().x(), piece->getBoardPos().y(),
                             1+npos.x(),1+npos.y());
    if(ok){
       piece->moveTo(npos, ncoordspos);
       clearImages();
       createHalfPieces(genereJustImages, white ? 7 : 1, white ? 13 : 7);
       return true;
    }else
        QMessageBox::information(this, "Error", "Так ходить нельзя!");
    return false;
}

void MainWindow::checkUpdate(){
    bool isCourseWhites = DataBase::is_current(_id_game);
    course = isCourseWhites ^ !white;//если ходят белые и мы белые, то наш ход
    if(course){
        controller->setCursorText(true);
        updateTimer.stop();
        updatePiece();
        update();
    }
    //std::cout << "checkUpdate()" << std::endl;
}


void MainWindow::updatePiece(){
    clearBoard();
    createPiece();
}

void MainWindow::paintEvent(QPaintEvent *){

    auto map = QPixmap(QString(":/other/bg-chess.xcf"));//":/other/bg-chess.jpg"));


    QPainter paint;
    paint.begin(this);
    QBrush brush;
    brush.setTexture(map);
    //brush.setStyle(Qt::RadialGradientPattern);
    paint.setBrush(brush);//(QBrush (QColor (255, 255, 255, 200)));
    paint.setPen (Qt::NoPen);
    paint.drawRect (0, 0, width(), height());
    paint.end();
}

MainWindow::~MainWindow()
{
    updateTimer.stop();
    for(auto x : labels_for_delete){
        delete x;
    }
    DataBase::closeDB();
    delete ui;
}
