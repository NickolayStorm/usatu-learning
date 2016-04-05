#include "unfinishedgames.h"
#include "ui_unfinishedgames.h"
#include "database.h"
UnfinishedGames::UnfinishedGames(QWidget *parent, QString _id) :
    QWidget(parent),
    ui(new Ui::UnfinishedGames)
{
    ui->setupUi(this);

    id = _id;
    DataBase::initDB();

    QSqlQueryModel* model = DataBase::get_unfiniched_games(id, ides);
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Белые"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Чёрные"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date & Time"));
    /*
        model->setHeaderData(0, Qt::Horizontal, QObject::tr("Nick"));
        model->setHeaderData(2, Qt::Horizontal, QObject::tr("Online"));
        model->setHeaderData(1, Qt::Horizontal, QObject::tr("Registration"));*/
        //model->setHeaderData(3, Qt::Horizontal, QObject::tr("Salary"));
    ui->tableView->setModel(model);
    ui->tableView->resizeRowsToContents();
    ui->tableView->horizontalHeader()->setStretchLastSection(true);
    connect(ui->tableView, SIGNAL(clicked(QModelIndex)), this, SLOT(selectAllRow(QModelIndex)));
    connect(this, SIGNAL(selectRow(int)), ui->tableView, SLOT(selectRow(int)));
    connect(this, SIGNAL(deselect()), ui->tableView, SLOT(clearSelection()));

}

int UnfinishedGames::getSelectId(){
    return ides[currentSelectedRow];
}

void UnfinishedGames::updateData(){
    QSqlQueryModel* model = DataBase::get_unfiniched_games(id, ides);
    model->setHeaderData(0, Qt::Horizontal, QObject::tr("Player 1"));
    model->setHeaderData(1, Qt::Horizontal, QObject::tr("Player 2"));
    model->setHeaderData(2, Qt::Horizontal, QObject::tr("Date & Time"));
    ui->tableView->setModel(model);
}

void UnfinishedGames::selectAllRow(QModelIndex index){
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

QModelIndexList UnfinishedGames::getSelectedRows(){
    return ui->tableView->selectionModel()->selectedIndexes();
}

UnfinishedGames::~UnfinishedGames()
{
    DataBase::closeDB();
    delete ui;
}
