//
// Created by pach on 4/15/24.
//

#ifndef IOTSERVER_DATABASEHOLDER_H
#define IOTSERVER_DATABASEHOLDER_H

#include <iostream>
#include "mariadb/conncpp.hpp"
#include "jsonReader.h"


class DBdevice;

using namespace std;

class databaseHolder {
public:

    databaseHolder();
    static sql::ResultSet *execPreparedQuery(string statement, vector<string> values, sql::Connection* connection);
    static sql::Connection* initDatabase(std::string host, int port, std::string username, std::string passwd, std::string dbName);

protected:

};


#endif //IOTSERVER_DATABASEHOLDER_H
