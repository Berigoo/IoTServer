//
// Created by pach on 4/14/24.
//

#include "ssl.h"

ssl::ssl(const char *sslCert, const char *sslKey) : httplib::SSLServer(sslCert, sslKey) {
    if(!httplib::SSLServer::is_valid())
        throw std::runtime_error("Server not valid");
}

void ssl::run(std::string host, int port) {
    listen(host, port);
}
