//
// Created by pach on 4/14/24.
//

#ifndef IOTSERVER_SSL_H
#define IOTSERVER_SSL_H

#define CPPHTTPLIB_OPENSSL_SUPPORT
#include "httplib.h"

class ssl : public httplib::SSLServer {
public:
    ssl(const char* sslCert, const char* sslKey);

    void run(std::string host, int port);
};


#endif //IOTSERVER_SSL_H
