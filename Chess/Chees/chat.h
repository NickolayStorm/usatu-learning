#ifndef CHAT_H
#define CHAT_H
#include "allmessages.h"
#include <QWidget>
#include "controlwidget.h"
#include "database.h"
#include <QTimer>
namespace Ui {
class Chat;
}

class Chat : public QWidget
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent*);
    explicit Chat(QWidget *controlWidget = 0, QWidget *p = 0, QString id_game = "", QString id_player = "");
    ~Chat();
public slots:
    void showNewMessages();
    void addMessage();

private:
    QTimer checkUpdate;
    QString _id_game;
    QString _id_player;
    Ui::Chat *ui;
    AllMessages *messages;
    QWidget *controlWidget;
};

#endif // CHAT_H
