#include "message.h"
#include <QString>
#include <QPainter>
#define MAX_COUNT_CHARS_ONA_LINE 30
Message::Message(QWidget *parent, QString t, bool _myMess) : QWidget(parent)
{
    QString tmp = t;
    //text = t;
    myMess = _myMess;
    char *chars;
    char newStr[MAX_COUNT_CHARS_ONA_LINE + 2];
    char *pnewStr = (char*)newStr;

    chars = (char*)tmp.toStdString().c_str();

    short count = 0;
    lines = 1;

    while(*chars){
        *pnewStr = *chars;
        ++chars;
        ++pnewStr;
        if(count == 30){
            *pnewStr = '\0';
            pnewStr = (char*)newStr;
            text.push_back(QString(pnewStr));
            ++lines;
            count = 0;
        }
        count++;
    }
    pnewStr = '\0';
    pnewStr = (char*)newStr;
    text.push_back(QString(pnewStr));
    this->setGeometry(0,0, 300, lines * 10);
}

void Message::paintEvent(QPaintEvent *){
    QPainter painter(this);
//    QBrush brush;
    painter.setPen(Qt::NoPen);
    QBrush brush(QColor(102, 205, 170, 255));
    brush.setStyle(Qt::SolidPattern);
    painter.setBrush(brush);

    painter.setRenderHint(QPainter::Antialiasing);
    painter.drawRoundedRect(0,0,this->width(), this->height(), 5, 3);
    QPen pen;
    pen.setWidth(2);
    painter.setPen(pen);
    brush.setColor(QColor(0,0,0, 255));
    painter.setBrush(brush);
    int delta = 20;
    for(auto x : text){
        painter.drawText(QPoint(5, delta), x);
        delta+=25;
    }
}

Message::~Message()
{

}

