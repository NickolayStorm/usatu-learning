#include "chat.h"
#include "ui_chat.h"
#include "message.h"
#include <QPainter>
#include <QPalette>
#include "allmessages.h"
Chat::Chat(QWidget *parent, QWidget *p, QString id_game, QString id_player) :
    QWidget(parent),
    ui(new Ui::Chat)
{
    controlWidget = p;
    ui->setupUi(this);
    ui->textField->setHorizontalScrollBarPolicy(Qt::ScrollBarAlwaysOff);
    messages = new AllMessages(this);
    DataBase::initDB();
    _id_player = id_player;
    _id_game = id_game;
    vector<mes> m = DataBase::getNewMessages(id_game,id_player, true);
    //vector<Message*> mess;
    for(auto x : m){
        messages->addMessage(new Message(messages, x.text, x.my));
    }


    ui->messagesArea->setVerticalScrollBarPolicy(Qt::ScrollBarAlwaysOn);
    //ui->area->setLayout(layout);
    ui->messagesArea->setWidget(messages);
   // checkUpdate.timeout();
    connect(&checkUpdate, SIGNAL(timeout()), this, SLOT(showNewMessages()));
    checkUpdate.start(1000);
    connect(ui->send, SIGNAL(clicked()), this, SLOT(addMessage()));
}

void Chat::showNewMessages(){
    cout << "update()" << endl;
    vector<mes> m = DataBase::getNewMessages(_id_game, _id_player, false, QDateTime::currentDateTime());
    for(auto x : m){
        messages->addMessage(new Message(messages, x.text, x.my));
    }
}

void Chat::addMessage(){

    DataBase::addNewMessage(_id_game, _id_player, ui->textField->toPlainText());
    ui->textField->clear();
    showNewMessages();
}

void Chat::paintEvent(QPaintEvent *){
        QPainter paint;
        paint.begin(this);
        paint.setBrush (QBrush (QColor (255, 255, 255, 255)));
        paint.setPen (Qt::NoPen);
        paint.drawRect (0, 0, width(), height());
        paint.end();
}

Chat::~Chat()
{
    delete ui;
}
