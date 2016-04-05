#include "controlwidget.h"
#include "ui_controlwidget.h"
#include <QPainter>
#include <QPalette>
#include <chat.h>

ControlWidget::ControlWidget(QWidget *parent, QString id_game, QString id_player) :
    QWidget(parent),
    ui(new Ui::ControlWidget)
{
    ui->setupUi(this);
    _id_game = id_game;
    _id_player = id_player;
    connect(ui->chat, SIGNAL(clicked()), this, SLOT(openChat()));
}

void ControlWidget::setCursorText(bool course){
    const QString yourCourse ("Ваш ход.");
    const QString notYourCourse ("Ход противника.");
    if(course){
        ui->course->setText(yourCourse);
    }else{
        ui->course->setText(notYourCourse);
    }
}

void ControlWidget::openChat(){
//    chatOpen = true;
//    update();
    if(chat == nullptr){
        chat = new Chat(nullptr, this, _id_game, _id_player);
        //chat->move(ui->chat->pos() - QPoint(50, 300));
        //chat->setGeometry(ui->chat->geometry());
    }
    chat->show();
}

void ControlWidget::chatClosed(){
    chat = nullptr;
}

//#define HEIGHT 400
//#define WIDTH 200
//#define DELTA_X 0
//#define DELTA_Y 100
void ControlWidget::paintEvent(QPaintEvent *){
    QPainter painter;
    painter.begin(this);
    QBrush brush(QColor (240, 240, 240, 240));
    painter.setBrush(brush);
    painter.setRenderHint(QPainter::Antialiasing);
    painter.setPen (Qt::NoPen);
    painter.drawRoundedRect(0,0,this->width(), this->height(), 15, 8);
    painter.end();
}

ControlWidget::~ControlWidget()
{
    delete ui;
}
