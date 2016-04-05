#ifndef CONTROLWIDGET_H
#define CONTROLWIDGET_H

#include <QWidget>
#include "chat.h"
namespace Ui {
class ControlWidget;
}

class ControlWidget : public QWidget
{
    Q_OBJECT

public:
    explicit ControlWidget(QWidget *parent = 0, QString id_game = "", QString id_player = "");
    void paintEvent(QPaintEvent*);
    void setCursorText(bool course);
    ~ControlWidget();

public slots:
    void chatClosed();
    void openChat();

private:
    QWidget *chat = nullptr;
    Ui::ControlWidget *ui;
    bool chatOpen = false;
    QString _id_game;
    QString _id_player;
};

#endif // CONTROLWIDGET_H
