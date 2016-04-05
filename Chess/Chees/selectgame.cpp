#include "selectgame.h"
#include "ui_selectgame.h"
#include <QPainter>
#include <QPushButton>
#include <iostream>
#include <QMessageBox>
#include "mainwindow.h"
#include "database.h"

using namespace std;
SelectGame::SelectGame(QWidget *parent, QString _id) :
    QMainWindow(parent),
    ui(new Ui::SelectGame)
{
    ui->setupUi(this);
    id = _id;

    QWidget *centWindow = new QWidget(this);
    //centralWidget->setGeometry(0,0,450,420);
    auto createButtonSelect = [](QWidget *parent, QWidget *connectingWindow){
        QPushButton *b = new QPushButton(parent);
        b->setObjectName(QString("select"));
        b->setStyleSheet(QString("QPushButton#select{"
                                 "color: white;"
                                 "text-decoration: none;"
                                 "padding: 3px;"
                                 "border-radius: 3px;"
                                 "background: rgb(53, 167, 110);"
                                 "width: 191px;"
                                 "height:27px;"
                                 "}"
                                 "QPushButton#select:hover{background: #C88;} "
                                 ));
        b->setText(QString("Выбрать!"));
        b->setGeometry(450,350,191,27);
        b->show();
        connect(b, SIGNAL(clicked()), connectingWindow, SLOT(select()));
    };

    createButtonSelect(centWindow, this);

    auto createButtonUpdate = [](QWidget *parent, QWidget *connecting){
        QPushButton *b = new QPushButton(parent);
        b->setObjectName(QString("update"));
        b->setText(QString("Обновить"));
        b->setGeometry(480,50,131,27);
        b->show();
        connect(b, SIGNAL(clicked()), connecting, SLOT(startUpdateTimer()));
    };
    createButtonUpdate(centWindow, this);
    tabs = new QTabWidget(centWindow);
    tabs->move(25,20);
    tabs->setFixedSize(390, 360);
    unfinished = new UnfinishedGames(0, id);
    tabs->addTab(unfinished,"Незаконченные игры");
    newGame = new NewGame(0, id);
    tabs->addTab(newGame,"Новая игра");
    this->setCentralWidget(centWindow);

}

void SelectGame::on_hidebutton_clicked(){
    int selectedId = unfinished->getSelectId();
    bool white = DataBase::is_white(selectedId, id);
    MainWindow * w = new MainWindow(nullptr, QString("%1").arg(selectedId), id, white);
    this->hide();
    cout << "clicked" << endl;
}

void SelectGame::startUpdateTimer(){
    if(up == nullptr) up = new QTimer(this);
    up->connect(up, SIGNAL(timeout()), this, SLOT(updateDataTabs()));
    QMovie *movie = new QMovie(":/other/other/load.gif");
    if(animation == nullptr){
        animation = new QLabel(this);
        animation->setGeometry(513,120,64,64);
        animation->setMovie(movie);
    }
    animation->show();
    movie->start();
    up->start(1500);
}

void SelectGame::updateDataTabs(){
    up->disconnect(up, SIGNAL(timeout()), this, SLOT(updateDataTabs()));
    if(tabs->currentWidget() == unfinished)
        unfinished->updateData();
    else if(tabs->currentWidget() == newGame)
        newGame->updateData();
    animation->hide();
}

void SelectGame::select(){
    if(tabs->currentWidget() == unfinished){
        QList<QModelIndex> rows = unfinished->getSelectedRows();
        int size = rows.size();
        if(size != 0){
            if(size == 3){//лол капец п р о в е р о ч к а

                //MainWindow * w = new MainWindow(nullptr, QString("%1").arg(selectedId), id, white);
                //w->show();
                //this->hide();
                on_hidebutton_clicked();
            }else QMessageBox::information(this, "Error", "Пожалуйста, выберите только одну игру");
        }else QMessageBox::information(this, "Error", "Пожалуйста, выберите игру");
    }else
        if(tabs->currentWidget() == newGame){
            QList<QModelIndex> rows = newGame->getSelectedRows();
            int size = rows.size();
            if(size != 0){
                if(size == 4){//лол капец п р о в е р о ч к а
                    int selectedId = newGame->getSelectId();
                    QString id_game;
                    bool ok = DataBase::create_new_game(id, selectedId, id_game);
                    if(ok){
                        MainWindow * w = new MainWindow(nullptr, id_game, id, true);
                        w->show();
                        this->hide();
                    }else QMessageBox::information(this, "Error", "Произошла внутренняя ошибка. Попробуйте позднее.");
                }else QMessageBox::information(this, "Error", "Пожалуйста, выберите только одну игру");
            }else QMessageBox::information(this, "Error", "Пожалуйста, выберите игру");
        }
}

void SelectGame::paintEvent(QPaintEvent *){
    QPainter paint;
    paint.begin(this);
    paint.setBrush (QBrush (QColor (255, 255, 255, 255)));
    paint.setPen (Qt::NoPen);
    paint.drawRect (0, 0, width(), height());
    paint.end();
}

SelectGame::~SelectGame()
{
    delete ui;
}
