//
// Created by pach on 4/15/24.
//

#include "databaseHolder.h"

//TODO fix this things
// make model-like databse (just like laravel no)

sql::ResultSet *databaseHolder::execPreparedQuery(string statement, vector<string> values, sql::Connection* connection) {
    shared_ptr<sql::PreparedStatement> stmt(connection->prepareStatement(statement));
    try {
        for (int i = 1; i <= values.size(); i++) stmt->setString(i, values[i - 1]);
        sql::ResultSet *tmp(stmt->executeQuery());
        return tmp;
    } catch (sql::SQLException &e) {
        cerr << "Error reading database: " <<
             e.what() << endl;
    }
    return nullptr;
}

sql::Connection* databaseHolder::initDatabase(std::string host, int port, std::string username, std::string passwd, std::string dbName) {
    sql::SQLString url;
    url = "jdbc:mariadb://" + host + ":" + to_string(port) + "/" + dbName;
    sql::Driver* driver = sql::mariadb::get_driver_instance();
    sql::Connection* connectionTmp(driver->connect(url, username, passwd));
    if (!connectionTmp)
        throw std::runtime_error("Failed to connect into database");
    return connectionTmp;
}

databaseHolder::databaseHolder() {

}