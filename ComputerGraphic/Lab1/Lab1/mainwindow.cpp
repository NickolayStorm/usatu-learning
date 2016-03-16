#include "mainwindow.h"
#include "ui_mainwindow.h"
#include "dimensional.h"
#include "controller.h"
#include "complex.h"


MainWindow::MainWindow(QWidget *parent) :
    QMainWindow(parent),
    ui(new Ui::MainWindow)
{
    ui->setupUi(this);
    DimensionalDrawing* dimensional;
    dimensional = new DimensionalDrawing(this);
    ui->widgets_layout->replaceWidget(ui->w1, dimensional);

    ComplexDrawing* complex = new ComplexDrawing(this);
    ui->widgets_layout->replaceWidget(ui->w2, complex);

    connect(ui->sliderAlpha, SIGNAL(valueChanged(int)), this, SLOT(alphaChanged(int)));
    connect(ui->sliderX, SIGNAL(valueChanged(int)), this, SLOT(xChanged()));
    connect(ui->sliderY, SIGNAL(valueChanged(int)), this, SLOT(yChanged()));
    connect(ui->sliderZ, SIGNAL(valueChanged(int)), this, SLOT(zChanged()));
}

void MainWindow::alphaChanged(int alpha){
    Controller::instance()->setAlpha(alpha);
    ui->labelAlpha->setText(QString().sprintf("%i", alpha));
}


void MainWindow::xChanged(){
    Controller::instance()->setPoint(ui->sliderX->value(), ui->sliderY->value(), ui->sliderZ->value());
    ui->labelX->setText(QString().sprintf("%i", ui->sliderX->value()));
}


void MainWindow::yChanged(){
    Controller::instance()->setPoint(ui->sliderX->value(), ui->sliderY->value(), ui->sliderZ->value());
    ui->labelY->setText(QString().sprintf("%i", ui->sliderY->value()));
}


void MainWindow::zChanged(){
    Controller::instance()->setPoint(ui->sliderX->value(), ui->sliderY->value(), ui->sliderZ->value());
    ui->labelZ->setText(QString().sprintf("%i", ui->sliderZ->value()));
}



void MainWindow::updateAll(){
    emit updateElems();
}

MainWindow::~MainWindow()
{
    delete ui;
}
