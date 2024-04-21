//
// Created by pach on 4/16/24.
//

#include "DBdevice.h"

#include <utility>

std::string DBdevice::host = "localhost";
int DBdevice::port = 3306;
std::string DBdevice::username = "iot";
std::string DBdevice::passwd = "passwd";
std::string DBdevice::dbName = "iot";
sql::Connection* DBdevice::connection = DBdevice::initDatabase(host, port, username, passwd, dbName);

sql::ResultSet *DBdevice::execPreparedQuery(string statement, vector<string> values) {
    return databaseHolder::execPreparedQuery(std::move(statement), std::move(values), DBdevice::connection);
}

bool DBdevice::checkUserCredentials(std::string username, std::string passwd) {
    try {
        sql::ResultSet *res = DBdevice::execPreparedQuery(
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
