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
