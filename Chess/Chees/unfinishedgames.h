#ifndef UNFINISHEDGAMES_H
#define UNFINISHEDGAMES_H
#include <QSqlQueryModel>
#include <QWidget>
#include <vector>
using std::vector;
namespace Ui {
class UnfinishedGames;
}

class UnfinishedGames : public QWidget
{
    Q_OBJECT

public:
    explicit UnfinishedGames(QWidget *parent = 0, QString _id = QString());
    void updateData();
    ~UnfinishedGames();
    QModelIndexList getSelectedRows();
    int getSelectId();

public slots:
    void selectAllRow(QModelIndex);

signals:
    void selectRow(int);
    void deselect();
private:
    QString id;
    Ui::UnfinishedGames *ui;
    int currentSelectedRow = -1;
    vector<int> ides;
};

#endif // UNFINISHEDGAMES_H
