#ifndef SELECTGAME_H
#define SELECTGAME_H

#include <QMainWindow>
#include <QTimer>
#include <QMovie>
#include <QLabel>
#include "unfinishedgames.h"
#include "newgame.h"
namespace Ui {
class SelectGame;
}

class SelectGame : public QMainWindow
{
    Q_OBJECT

public:
    explicit SelectGame(QWidget *parent = 0, QString _id = QString());
    void paintEvent(QPaintEvent *);
    ~SelectGame();
public slots:
    void updateDataTabs();
    void select();
    void startUpdateTimer();
private slots:
    void on_hidebutton_clicked();
private:
    QLabel *animation = nullptr;
    QTimer *up = nullptr;
    QString id;
    QTabWidget *tabs;
    UnfinishedGames *unfinished;
    NewGame *newGame;
    Ui::SelectGame *ui;
};

#endif // SELECTGAME_H
