#include "registration.h"
#include "ui_registration.h"
#include <QTimer>
#include <QMovie>
#include <QMessageBox>
#include <QPainter>
#include "database.h"

Registration::Registration(QWidget *parent, QWidget *prev) :
    QWidget(parent),
    ui(new Ui::Registration)
{
    ui->setupUi(this);
    ui->editPassword->setEchoMode(QLineEdit::Password);

    setTabOrder(ui->login, ui->editPassword);
    setTabOrder(ui->editPassword, ui->registration);



    login = prev;
    this->setStyleSheet("QPushButton#registration{"
                            " color: white;"
                            "text-decoration: none;"
                            "padding: 3px;"
                            "border-radius: 3px;"
                            "background: rgb(53, 167, 110)"
                    "}"
                    "QPushButton#registration:hover{background: #C88;}");
    connect(ui->registration, SIGNAL(clicked()), this, SLOT(initAnimation()));
    //connect(ui->registration, SIGNAL(clicked()), )
}

void Registration::initAnimation(){
    if(ui->login->text().size() != 0 && ui->editPassword->text().size() != 0){

        QMovie *movie = new QMovie(":/other/other/load.gif");
        animation = new QLabel(this);
        animation->setGeometry(QRect(280,20,64,64));
        animation->setMovie(movie);
        animation->show();
        movie->start();

        DataBase::initDB();
        error = DataBase::create_new_user(ui->login->text(), ui->editPassword->text(), *&reg_exist);
        if(load == nullptr)
                load = new QTimer(this);
         connect(load, SIGNAL(timeout()), this, SLOT(check()));
         load->start(2000);//5000);
        //}else QMessageBox::information(this, "Error", error);
    }else QMessageBox::information(this, "Error", "Please fill in all the fields");
}

void Registration::check(){
    load->stop();
    animation->hide();
    reg_started = true;
    if(reg_exist){
        //ok, timer to close and open registration
        open_auth = new QTimer(this);
        connect(open_auth, SIGNAL(timeout()), this, SLOT(openAuthorization()));
        open_auth->start(500);
    }else{
        isError = true;
        QMessageBox::information(this, "Error", error);
    }
}

void Registration::openAuthorization(){
    open_auth->stop();
    reg_started = false;
    reg_exist = false;
    isError = false;
    ui->login->setText("");
    ui->editPassword->setText("");
    login->show();
    this->hide();
}

void Registration::paintEvent(QPaintEvent *){
    QPainter paint;
    paint.begin(this);
    paint.setBrush (QBrush (QColor (255, 255, 255, 255)));
    paint.setPen (Qt::NoPen);
    paint.drawRect (0, 0, width(), height());
    if(reg_started){
        if(!isError){
            paint.drawImage(280,20,QImage(":/other/other/ok.png"));
        }
        else {
            paint.drawImage(280,20,QImage(":/other/other/error.png"));
            //delete load;
            //load = nullptr;
            //
            //paint.drawText(200,104, QString("Пара логин-пароль не совпадает."));

        }
    }
    paint.end();
}

Registration::~Registration()
{
    login->show();
    delete ui;
}
