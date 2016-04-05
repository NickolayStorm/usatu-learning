#include "database.h"
#include <QSqlQueryModel>
bool DataBase::initDB()
{
    if(!DataBase::getDB().isOpen()){
        QSqlDatabase db = QSqlDatabase::addDatabase("QPSQL");
        db.setHostName("127.0.0.1");
        db.setDatabaseName("LAB3");
        db.setUserName("postgres");
        db.setPassword("1111");
        db.open();

        bool isOpen = db.isOpen();
        if (!isOpen)
            cout << "ERROR: DB is not openned." <<endl;
        else
            cout << "SUCCESS: DB is openned." << endl;
        return isOpen;
    }
    cout << "DB is ALREADY openned." << endl;
    return true;
}

void DataBase::addNewMessage(QString id_game, QString id_player, QString text){
    QSqlQuery query;
    query.prepare("INSERT INTO message(id_game, id_player, text) VALUES (?, ?, ?);");
    query.addBindValue(id_game);
    query.addBindValue(id_player);
    query.addBindValue(text);
    query.exec();
}

QSqlQueryModel* DataBase::get_online_players_model(QString& id, vector<int> &ides){
    cout << "get_online_players_model()" <<endl;
    auto model = new QSqlQueryModel();
    model->setQuery(QString("SELECT nick, reg_date, \"online\", \"rating\" FROM player WHERE player.online = TRUE AND id <> %1;").arg(id));


    ides.clear();
    QSqlQuery query;
    query.prepare(QString("SELECT id FROM player WHERE player.online = TRUE AND id <> ?;"));
    query.addBindValue(id);
    query.exec();
    while(query.next()){
        ides.push_back(query.value(0).toInt());
    }
    return model;
}

QSqlQueryModel*DataBase::get_unfiniched_games(QString &nick, vector<int> &ides){
    cout << "get_unfiniched_games()" <<endl;
    auto model = new QSqlQueryModel();
    model->setQuery(QString("SELECT p.nick, q.nick, start_time from games INNER JOIN player p ON p.id = player_1 INNER JOIN player q ON q.id = player_2 WHERE complete = FALSE AND player_1 = ").append(nick).append(" OR player_2 = ").append(nick).append(";"));
    ides.clear();
    QSqlQuery query;
    query.prepare(QString("SELECT games.id FROM games INNER JOIN player p ON p.id = player_1 INNER JOIN player q ON q.id = player_2 WHERE complete = FALSE AND player_1 = ? OR player_2 = ?;"));
    query.addBindValue(nick);
    query.addBindValue(nick);

    if (!query.exec()) cout << query.lastError().text().toStdString()<<endl;
    while(query.next()){
        ides.push_back(query.value(0).toInt());
    }
    return model;
}

QSqlDatabase DataBase::getDB(){
    return QSqlDatabase::database();
}

QString DataBase::identity(QString name, QString pass, bool &ok){
    cout << "identity()" <<endl;
    if(name.size() < 26 && pass.size() < 26){
        QSqlQuery query;
        query.prepare("SELECT get_id_by_name(?, ?)");
        query.addBindValue(name);
        query.addBindValue(pass);
        if(!query.exec()){
            //err = query.lastError().text();
            ok = false;
            return QString();
        }
        ok = query.next();
        QString result = query.value(0).toString();

        if(ok)
            if(result != 0)
                return result;
        ok = false;
        return QString();
    }
    ok = false;
    return QString();
}

QString DataBase::create_new_user(QString login, QString pass, bool &ok){
    cout << "create_new_user()" <<endl;
    if(login.size() < 26 && pass.size() < 26){
        if(check_unique_nick(login)){
            QSqlQuery query;
            query.prepare("INSERT INTO player(nick, pas_hash) VALUES(?, ?)");
            query.addBindValue(login);
            query.addBindValue(pass);
            if(!query.exec()){
                ok = false;
                return query.lastError().text();
            }else{
                ok = true;
                return "";
            }

        }else{
            ok = false;
            return QString("User with this login is already exist!");
        }
    }else {
        ok = false;
        return QString("Login and password cannot be biggest of 25 char's!");
    }
}

bool DataBase::check_unique_nick(QString& name){
    cout << "check_unique_nick()" <<endl;
    QSqlQuery query;
    query.prepare("SELECT check_uniqe_new_player(?)");
    query.addBindValue(name);
    query.exec();
    query.next();
    return query.value(0).toBool();
}

bool DataBase::get_positions_for_pieces(QString &id_game, QString &id_piece, vector<int> &pos_ah, vector<int> &pos_18){
    cout << "get_positions_for_pieces()" <<endl;
    QSqlQuery query;
    query.prepare(" SELECT \"isExist\", \"cell_ah\", \"cell_18\" FROM state WHERE id_game = ? AND id_piece = ?;");
    query.addBindValue(id_game);
    query.addBindValue(id_piece);
    if(!query.exec()){
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    while(query.next()){
        if(query.value(0).toBool()){//if exist
            pos_ah.push_back(query.value(1).toInt());
            pos_18.push_back(query.value(2).toInt());
        }
        else{
            pos_ah.push_back(0);
            pos_18.push_back(0);
        }
    }
    return true;
}

vector<mes> DataBase::getNewMessages(QString &id_game, QString &id_player, bool firstUpdate, QDateTime lUp){

    QString lastUpdate;
    if(firstUpdate == true){
        QSqlQuery t;
        t.prepare("SELECT start_time FROM games WHERE id = ?;");
        t.addBindValue(id_game);
        t.exec();
        t.next();

        QString tmp = t.value(0).toString();
        const char *ch = tmp.toStdString().c_str();
        char *pchar = (char*)ch;
        while(*pchar){
            if(*pchar == 'T'){
                *pchar = ' ';
            }
            ++pchar;
        }

        QString rz(ch);
        lastUpdate = rz;
    }else lastUpdate = lUp.toString("yyyy-MM-dd hh:mm:ss");
    cout << "Time: " << lastUpdate.toStdString() << endl;
    QSqlQuery query;
    query.prepare("SELECT text, time FROM message WHERE time > ? AND id_game = ?");
    query.addBindValue(lastUpdate);
    query.addBindValue(id_game);

    vector<mes> rez;

    if(!query.exec()){
          cout << query.lastError().text().toStdString() <<endl;

    }else{
    while(query.next()){
        struct mes m = {
            query.value(0).toString(),
                    query.value(1).toDateTime(),
                    false
        };
        rez.push_back(m);
    }

    cout << 232 << endl;
    std::sort(rez.begin(), rez.end(), [](auto fst, auto snd)->bool{return fst.time < snd.time;});

    }
    return rez;

//    QString lastUpdate;
//    QSqlQuery query;
//    query.prepare("SELECT text, time FROM message WHERE time > ? AND id_game = ? AND id_player = ?;");
//    cout << "id_player: " << id_game.toStdString() << endl;
//    cout << "id_game: " << id_player.toStdString() << endl;

//    if(firstUpdate == true){
//        QSqlQuery t;
//        t.prepare("SELECT start_time FROM games WHERE id = ?;");
//        t.addBindValue(id_game);
//        t.exec();
//        t.next();
//        lastUpdate = t.value(0).toString();

//    }else lastUpdate = lUp.toString("yyyy-MM-dd hh:mm:ss");

//    cout << lastUpdate.toStdString() <<endl;

//    const char *ch = lastUpdate.toStdString().c_str();
//    char *pchar = (char*)ch;
//    while(*pchar){
//        if(*pchar == 'T'){
//            *pchar = ' ';
//        }
//        ++pchar;
//    }
//    QString zalupa(ch);
//    query.addBindValue(zalupa);

//    query.addBindValue(id_game);
//    query.addBindValue(id_player);

//    if(!query.exec()){
//        cout << query.lastError().text().toStdString() <<endl;
//        cout << "!!!!!" <<endl;
//    }

//    vector<mes> rez;
//    while(query.next()){
//        struct mes m = {
//            query.value(0).toString(),
//            query.value(1).toDateTime(),
//            true
//        };
//        rez.push_back(m);
//    }
//    cout << "202" << endl;
//    QString player_2;
//    query.prepare("SELECT player_2 FROM games WHERE player_1 = ?;");
//    query.addBindValue(id_player);
//    if(!query.exec()){
//         cout << query.lastError().text().toStdString() <<endl;
//    }
//    query.next();
//    player_2 = query.value(0).toString();

//    query.clear();
//    query.prepare("SELECT text, time FROM message WHERE time > ? AND id_game = ? AND id_player = ?");

//    query.addBindValue(lastUpdate);
//    query.addBindValue(id_game);
//    query.addBindValue(player_2);
//    cout << 217 << endl;
//    if(!query.exec()){
//        cout << query.lastError().text().toStdString() <<endl;
//    }
//    cout << 222 << endl;
//    while(query.next()){
//        struct mes m = {
//            query.value(0).toString(),
//            query.value(1).toDateTime(),
//            false
//        };
//        rez.push_back(m);
//    }

//    cout << 232 << endl;
//    std::sort(rez.begin(), rez.end(), [](auto fst, auto snd)->bool{return fst.time < snd.time;});
//    return rez;
}

bool DataBase::move(QString &id_player, QString &id_game, int id_piece,
                    int prev_ah, int prev_18,
                    int new_ah, int new_18){
    cout << "move(): prev: " << prev_ah << " "<< prev_18 << "\nnew: " << new_ah << " "<< new_18 <<endl;
    QSqlQuery query;
    query.prepare("SELECT move(?, ?, ?, ?, ?, ?, ?);");
    query.addBindValue(id_player);
    query.addBindValue(id_game);
    query.addBindValue(id_piece);
    query.addBindValue(prev_18);
    query.addBindValue(prev_ah);
    query.addBindValue(new_18);
    query.addBindValue(new_ah);
    if(!query.exec()){
        cout << query.lastError().text().toStdString() <<endl;
        return false;
    }
    query.next();
    //bool ok = query.value(0).toBool();
    return query.value(0).toBool();

}

//FUNCTION move(
//				_player_id INT, _id_game INT, _id_piece INT,
//				_prev_18 SMALLINT, _prev_ah SMALLINT,
//				_curr_18 SMALLINT, _curr_ah SMALLINT
//				)
//		RETURNS BOOLEAN

bool DataBase::create_new_game(QString &user, int id_player, QString& id_game){
    cout << "create_new_game()" <<endl;
    QSqlQuery query;
    query.prepare(QString("INSERT INTO games(player_1, player_2) VALUES(?, ?)"));
    query.addBindValue(user);
    query.addBindValue(id_player);
    if(!query.exec()){
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    query.clear();
    query.prepare("SELECT id FROM games WHERE player_1 = ? AND player_2 = ? ORDER BY start_time DESC;");
    query.addBindValue(user);
    query.addBindValue(id_player);
    if(!query.exec()){
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    query.next();
    id_game = query.value(0).toString();
    return true;
}

bool DataBase::is_current(QString& id_game){
    QSqlQuery query;
    query.prepare("SELECT move FROM games WHERE id = ?");
    query.addBindValue(id_game);
    if(!query.exec()){
        return false;
    }
    query.next();
    return query.value(0).toBool();
}

bool DataBase::is_white(int id_game, QString &id_player){
    cout << "is_white()" <<endl;
    QSqlQuery query;
    query.prepare(QString("SELECT * FROM games WHERE id = ? AND player_1 = ?;"));
    query.addBindValue(id_game);
    query.addBindValue(id_player);
    if(!query.exec()){
        cout << query.lastError().text().toStdString() << endl;
        return false;
    }
    return query.next();
}

void DataBase::closeDB(){
    cout << "DB is closed."<< endl;
    QSqlDatabase::database().close();
    //isOpen = QSqlDatabase::database().isOpen();
}

