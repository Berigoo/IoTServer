//
// Created by pach on 4/22/24.
//

// TODO make it secure (wss)

// TODO create websocket endpoint inheritance-able
//  for example the 'child' do not need to set up how the connection stored
//  'child' only responsible to how data processed after client send message or client connect also or client disconnect
//  (ws connections list on WS2, and also make it static)
//  WS -> WS2 -> ENDPOINT 1
//            -> ENDPOINT 2


#ifndef IOTSERVER_WEBSOCKET_H
#define IOTSERVER_WEBSOCKET_H

#include "websocketpp/config/asio_no_tls.hpp"
#include "websocketpp/server.hpp"
#include "map"
#include "jsonReader.h"
#include "../models/device.h"
#include "algorithm"

typedef websocketpp::server<websocketpp::config::asio> server;
typedef server::message_ptr message_ptr;
using websocketpp::lib::placeholders::_1;
using websocketpp::lib::placeholders::_2;

class websocket {
public:
    static std::map<std::string, server::connection_ptr> wsConnections;

    server svr;


    websocket();
    virtual ~websocket();

    virtual void onHttp(websocketpp::connection_hdl hdl);
    virtual void onFail(websocketpp::connection_hdl hdl);
    virtual void onClose(websocketpp::connection_hdl hdl);
    virtual void onMessage(websocketpp::connection_hdl hdl, message_ptr msg);
    virtual bool validate(websocketpp::connection_hdl hdl);
    virtual void onOpen(websocketpp::connection_hdl hdl);

    static bool isConnectionExist(server::connection_ptr conn_ptr);
    static bool isUuidExist(string uuid);
    static void closeAllEstablishedConns();

    void run(int port);

};

//void websocket::run(int port) {};


#endif //IOTSERVER_WEBSOCKET_H
