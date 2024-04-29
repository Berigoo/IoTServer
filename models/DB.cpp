//
// Created by pach on 4/16/24.
//

#include "DB.h"

#include <utility>

std::string DB::host = "localhost";
int DB::port = 3306;
std::string DB::username = "iot";
std::string DB::passwd = "passwd";
std::string DB::dbName = "iot";
sql::Connection* DB::connection = DB::initDatabase(host, port, username, passwd, dbName);

sql::ResultSet *DB::execPreparedQuery(string statement, vector<string> values) {
    return databaseHolder::execPreparedQuery(std::move(statement), std::move(values), DB::connection);
}

bool DB::checkUserCredentials(std::string username, std::string passwd) {
    try {
        sql::ResultSet *res = DB::execPreparedQuery(
                "SELECT COUNT(id) FROM users WHERE username=? AND passwd=?", {username, passwd}
        );
        if(res->next()){
            int count = res->getInt(1);
            if(count > 0) return true;
            else return false;
        }
    } catch (sql::SQLException& e){
        std::cout << "user validation error, " << e.what() << '\n';
        return false;
    }
}

sql::ResultSet *DB::getRightUUID(string leftUUID) {
    return execPreparedQuery("SELECT tmp.uuid, tmp.name, tmp.type, tmp.owner_id from "
                      "(SELECT uuid, name, type, owner_id from devices_relationship "
                      "INNER JOIN devices ON devices_relationship.`to` = devices.uuid "
                      "WHERE `from`=?) "
                      "AS tmp", {leftUUID});
}
