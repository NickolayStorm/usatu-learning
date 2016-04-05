#ifndef REGISTRATION_H
#define REGISTRATION_H

#include <QWidget>
#include <QLabel>
namespace Ui {
class Registration;
}

class Registration : public QWidget
{
    Q_OBJECT

public:
    explicit Registration(QWidget *parent = 0, QWidget* prev = nullptr);
    ~Registration();
    void paintEvent(QPaintEvent *);
public slots:
    void initAnimation();
    void check();
    void openAuthorization();

private:
    QLabel *animation;
    bool isError;
    QString error;
    QWidget *login;
    bool reg_started = false;
    bool reg_exist = false;
    QTimer *load = nullptr;
    QTimer *open_auth;
    Ui::Registration *ui;
};

#endif // REGISTRATION_H
