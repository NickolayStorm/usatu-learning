#ifndef MAINWINDOW_H
#define MAINWINDOW_H

#include <QMainWindow>

namespace Ui {
class MainWindow;
}

class MainWindow : public QMainWindow
{
    Q_OBJECT

public:
    explicit MainWindow(QWidget *parent = 0);
    ~MainWindow();
    void updateAll();
signals:
    void updateElems();

public slots:
    void alphaChanged(int);
    void xChanged();
    void yChanged();
    void zChanged();
private:
    Ui::MainWindow *ui;


};

#endif // MAINWINDOW_H
