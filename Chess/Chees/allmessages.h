#ifndef ALLMESSAGES_H
#define ALLMESSAGES_H

#include <QWidget>
#include "message.h"
namespace Ui {
class AllMessages;
}

class AllMessages : public QWidget
{
    Q_OBJECT

public:
    explicit AllMessages(QWidget *parent = 0);
    void addMessage(Message*);
    int getCursor(){
        return currCursorPos;
    }

    ~AllMessages();

private:
    int currCursorPos = 10;
    Ui::AllMessages *ui;
};

#endif // ALLMESSAGES_H
