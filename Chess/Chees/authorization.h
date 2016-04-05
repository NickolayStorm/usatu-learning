#ifndef AUTHORIZATION_H
#define AUTHORIZATION_H

#include <QImage>
#include <QWidget>
#include <QGraphicsScene>
#include <QGraphicsPixmapItem>
#include <QLabel>
namespace Ui {
class authorization;
}

class authorization : public QWidget
{
    Q_OBJECT

public:
    void paintEvent(QPaintEvent*);
    explicit authorization(QWidget *parent = 0);
    ~authorization();
public slots:
    void identetification();
    void check();
    void showAuthButton();


private slots:
    //void on_auth_clicked();
    void on_registration_clicked();

    void on_authoriz_clicked();

private:
    bool show_window = false;
    QWidget *registration = nullptr;
    QLabel *animation = nullptr;
    QTimer *load = nullptr;
    QTimer *close = nullptr;
    bool connectDB = false;
    bool identity = false;
    QString id;
    Ui::authorization *ui;
};

#endif // AUTHORIZATION_H
