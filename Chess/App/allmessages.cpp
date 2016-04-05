#include "allmessages.h"
#include "ui_allmessages.h"

AllMessages::AllMessages(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::AllMessages)
{
    ui->setupUi(this);
}

void AllMessages::addMessage(Message *mes){
    int dy = mes->height() + 10;
    mes->setGeometry(0, currCursorPos, mes->width(), mes->height());
    mes->show();
    currCursorPos += dy;
    this->setGeometry(0, 0, this->width(), this->height() + dy);
}

AllMessages::~AllMessages()
{
    delete ui;
}
