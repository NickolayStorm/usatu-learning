#include "newgame.h"
#include "ui_newgame.h"
#include "database.h"
#include <QTableWidget>
NewGame::NewGame(QWidget *parent, QString _id) :
    QWidget(parent),
    ui(new Ui::NewGame)
{
    ui->setupUi(this);

    id = _id;
    DataBase::initDB();

    QSqlQueryModel* model = DataBase::get_online_players_model(id, ides);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nick"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Online"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Registration"));
        model->setHeaderData(3, Qt::Horizontal, QObject::tr("Rat"));
        //model->setHeaderData(3, Qt::Horizontal, QObject::tr("Salary"));
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectAllRow(QModelIndex)));
    connect(this, SIGNAL(selectRow(int)), ui->tableView, SLOT(selectRow(int)));
    connect(this, SIGNAL(deselect()), ui->tableView, SLOT(clearSelection()));

}


void NewGame::updateData(){
    QSqlQueryModel* model = DataBase::get_online_players_model(id, ides);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nick"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Online"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Registration"));
    ui->tableView->setModel(model);
}

void NewGame::selectAllRow(QModelIndex index){
    int row = index.row();
    if(currentSelectedRow != row){
        currentSelectedRow = row;
        emit selectRow(row);
    }
    else{
        currentSelectedRow = -1;
        emit deselect();
    }
}

int NewGame::getSelectId(){
    return ides[currentSelectedRow];
}

QModelIndexList NewGame::getSelectedRows(){
    return ui->tableView->selectionModel()->selectedIndexes();
}

NewGame::~NewGame()
{
    DataBase::closeDB();
    delete ui;
}
