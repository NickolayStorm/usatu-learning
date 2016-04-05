#ifndef MESSAGE_H
#define MESSAGE_H
#include <QString>
#include <QWidget>

class Message : public QWidget
{
    Q_OBJECT
public:
    explicit Message(QWidget *parent = 0, QString t = "", bool _myMess = false);
    ~Message();
    QVector<QString> text;
    bool myMess;
    int lines;
    void paintEvent(QPaintEvent*);
signals:

public slots:
};

#endif // MESSAGE_H
