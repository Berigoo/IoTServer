//
// Created by pach on 4/22/24.
//

#ifndef IOTSERVER_WS_H
#define IOTSERVER_WS_H

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

class ws {
private:
    server svr;

public:
    ws();

    virtual void onHttp(websocketpp::connection_hdl hdl);
    virtual void onFail(websocketpp::connection_hdl hdl);
    virtual void onClose(websocketpp::connection_hdl hdl);
    virtual void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    virtual bool validate(websocketpp::connection_hdl hdl);
    virtual void onOpen(websocketpp::connection_hdl hdl);

    void run(int port);

};


#endif //IOTSERVER_WS_H
