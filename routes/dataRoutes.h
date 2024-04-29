//
// Created by pach on 4/15/24.
//

#ifndef IOTSERVER_DATAROUTES_H
#define IOTSERVER_DATAROUTES_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"
#include "../utils/jsonReader.h"
#include "../models/device.h"
#include "../models/data.h"
#include "../utils/jsonWriter.h"

class dataRoutes {
public:
    dataRoutes(httplib::SSLServer& server);

    static void dataSend(const httplib::Request& req, httplib::Response& res);
};


#endif //IOTSERVER_DATAROUTES_H
