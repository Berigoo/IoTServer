//
// Created by pach on 4/16/24.
//

#ifndef IOTSERVER_DBDEVICE_H
#define IOTSERVER_DBDEVICE_H

#include "../utils/databaseHolder.h"
#include "../utils/jsonReader.h"

class DBdevice : public databaseHolder{
public:
    static sql::Connection* connection;
    DBdevice();

    static std::string host;
    static int port;
    static std::string username;
    static std::string passwd;
    static std::string dbName;

    static sql::ResultSet *execPreparedQuery(string statement, vector<string> values);
    static bool checkUserCredentials(std::string username, std::string passwd);
};


#endif //IOTSERVER_DBDEVICE_H
