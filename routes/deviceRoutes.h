//
// Created by pach on 4/15/24.
//

#ifndef IOTSERVER_DEVICEROUTES_H
#define IOTSERVER_DEVICEROUTES_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "functional"
#include "../utils/databaseHolder.h"
#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_io.hpp"
#include "boost/uuid/uuid_generators.hpp"
#include "../models/device.h"
#include "spdlog/spdlog.h"

class deviceRoutes {
public:
    deviceRoutes(httplib::SSLServer& server);

private:
    void listDevices(const httplib::Request& req, httplib::Response& res);
    void addDevices(const httplib::Request& req, httplib::Response& res);
    void removeDevices(const httplib::Request& req, httplib::Response& res);
};


#endif //IOTSERVER_DEVICEROUTES_H
