#ifndef DATABASE_H
#define DATABASE_H
#include <QtSql>
#include <iostream>
#include <string>
#include <vector>
using namespace std;
struct mes{
    QString text;
    QDateTime time;
    bool my;

};

class DataBase
{
public:

    static bool initDB();
    static void closeDB();
    static QSqlDatabase getDB();
    //return id of player
    static QString identity(QString nick, QString pass, bool &ok);
    static QString create_new_user(QString login, QString pass, bool&ok);
    static bool check_unique_nick(QString&);
    static QSqlQueryModel *get_online_players_model(QString& id, vector<int> &ides);
    static QSqlQueryModel *get_unfiniched_games(QString& nick, vector<int> &ides);
    static bool get_positions_for_pieces(QString& id_game, QString& id_piece, vector<int> &pos_ah, vector<int> &pos_18);
    static bool move(QString &id_player, QString& id_game, int id_piece,
                     int prev_ah, int prev_18,
                     int new_ah, int new_18);
    static bool create_new_game(QString& user, int id_player, QString& id_game);
    static bool is_white(int id_game, QString& id_player);
    static bool is_current(QString& id_game);
    static vector<mes> getNewMessages(QString& id_game, QString& id_player, bool firstUpdate, QDateTime lastUpdate = QDateTime());
    static void addNewMessage(QString id_game, QString id_player, QString text);
};

#endif // DATABASE_H
