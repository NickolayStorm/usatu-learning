#include "authorization.h"
#include "ui_authorization.h"
#include <QMovie>
#include <QPainter>
#include <QTimer>
#include <database.h>
#include <QMessageBox>
#include "registration.h"
#include "selectgame.h"


authorization::authorization(QWidget *parent) :
    QWidget(parent),
    ui(new Ui::authorization)
{
    ui->setupUi(this);
    ui->editPassword->setEchoMode(QLineEdit::Password);
    ui->registration->hide();
    ui->authoriz->hide();
    setTabOrder(ui->login, ui->editPassword);
    setTabOrder(ui->editPassword, ui->ok);
    ui->quest->setFocusPolicy(Qt::NoFocus);
    this->setStyleSheet("QPushButton#quest{"
                    " color: white;"
                    "text-decoration: none;"
                    "padding: 3px;"
                    "border-radius: 3px;"
                    "background: #BBB"//#BBB"
                    "}"
                    "QPushButton#registration{"
                            " color: white;"
                            "text-decoration: none;"
                            "padding: 3px;"
                            "border-radius: 3px;"
                            "background: rgb(53, 167, 110)"
                    "}"
                    "QPushButton#registration:hover{background: #C88;} ");

    connect(ui->quest, SIGNAL(pressed()), ui->quest, SLOT(close()));
    connect(ui->quest, SIGNAL(pressed()), ui->registration, SLOT(show()));
    connect(ui->ok, SIGNAL(clicked()), this, SLOT(identetification()));

}

void authorization::identetification(){
    show_window = false;
    update();
    if(ui->login->text().size() != 0 && ui->editPassword->text().size() != 0){

        if(load != nullptr) delete load;
            load = new QTimer(this);
        if(animation != nullptr) delete animation;
        QMovie *movie = new QMovie(":/other/other/load.gif");
        animation = new QLabel(this);
        animation->setGeometry(QRect(270,20,64,64));
        animation->setMovie(movie);
        animation->show();
        movie->start();
        connect(load, SIGNAL(timeout()), this, SLOT(check()));
        load->start(2000);//5000);
        connectDB = DataBase::initDB();
        id = DataBase::identity(ui->login->text(), ui->editPassword->text(), *&identity);
    }
}

void authorization::check(){
    load->stop();

    //if ok
    //connectDB = initDB.get();
    show_window = true;
    if(connectDB){
        //QMovie *movie = new QMovie(":/other/other/ok.png");
        animation->hide();
        //animation->setMovie(movie);
        //identity = true;
        if(identity){
            close = new QTimer(this);
            connect(close, SIGNAL(timeout()), this, SLOT(showAuthButton()));
            close->start(500);
        }else QMessageBox::information(nullptr, "Error", "Пара логин-пароль не совпадает.");
    }
    else{
        QMessageBox::information(this, "Error", "Unable to create the database connection. Please check your Internet connection settings.");
        //this->destroy();
    }
}

void authorization::showAuthButton(){
    close->stop();
    ui->authoriz->show();
    ui->ok->hide();

}

void authorization::paintEvent(QPaintEvent *){
    QPainter paint;
    paint.begin(this);
    paint.setBrush (QBrush (QColor (255, 255, 255, 255)));
    paint.setPen (Qt::NoPen);
    paint.drawRect (0, 0, width(), height());
    if(show_window){
        if(identity){
            paint.drawImage(270,20,QImage(":/other/other/ok.png"));
        }
        else {
            QPen pen;
            pen.setColor(Qt::black);
            paint.setPen(pen);
            paint.setBrush (QBrush (QColor (0, 0, 0, 255)));
            paint.drawImage(270,20,QImage(":/other/other/error.png"));
            //delete load;QRect(280,15,64,64)
            //load = nullptr;
            //
            //paint.drawText(200,104, QString("Пара логин-пароль не совпадает."));

        }
    }
    paint.end();
}

authorization::~authorization()
{
    DataBase::closeDB();
    delete ui;

}

//void authorization::on_auth_clicked(){
//    QWidget *w = new SelectGame(0, id);
//    w->show();
//    this->hide();
//}

void authorization::on_registration_clicked()
{
    //this->setStyleSheet("QPushButton#registration{background: #BBB;}");
    ui->registration->hide();
    this->hide();
    if(registration == nullptr)
        registration = new Registration(NULL, this);
    registration->show();
    //cout << "OK" <<endl;
}

void authorization::on_authoriz_clicked()
{
    QWidget *w = new SelectGame(0, id);
    w->show();
    this->hide();
}
