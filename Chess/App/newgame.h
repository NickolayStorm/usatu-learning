#ifndef NEWGAME_H
#define NEWGAME_H
#include <QSqlQueryModel>
#include <QWidget>
#include <vector>
using std::vector;
namespace Ui {
class NewGame;
}

class NewGame : public QWidget
{
    Q_OBJECT

public:
    explicit NewGame(QWidget *parent = 0, QString _id = QString());
    ~NewGame();
    void updateData();
    QModelIndexList getSelectedRows();
    int getSelectId();
public slots:
    void selectAllRow(QModelIndex);

signals:
    void selectRow(int);
    void deselect();
private:
    QString id;
    Ui::NewGame *ui;
    int currentSelectedRow = -1;
    vector<int> ides;
};

#endif // NEWGAME_H
