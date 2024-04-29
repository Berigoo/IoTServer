//
// Created by pach on 4/16/24.
//

#ifndef IOTSERVER_DB_H
#define IOTSERVER_DB_H

#include "../utils/databaseHolder.h"
#include "../utils/jsonReader.h"

class DB : public databaseHolder{
public:
    static sql::Connection* connection;
    DB();

    static std::string host;
    static int port;
    static std::string username;
    static std::string passwd;
    static std::string dbName;

    static sql::ResultSet *execPreparedQuery(string statement, vector<string> values);
    static bool checkUserCredentials(std::string username, std::string passwd);
    static sql::ResultSet* getRightUUID(string leftUUID);
};


#endif //IOTSERVER_DB_H
