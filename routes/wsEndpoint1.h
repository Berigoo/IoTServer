//
// Created by pach on 4/23/24.
//

#ifndef IOTSERVER_WSENDPOINT1_H
#define IOTSERVER_WSENDPOINT1_H

#include "../utils/websocket.h"
#include "../utils/jsonWriter.h"

class wsEndpoint1 : public websocket{
    void onOpen(websocketpp::connection_hdl hdl) override;
    void onMessage(websocketpp::connection_hdl hdl, message_ptr msg) override;
};


#endif //IOTSERVER_WSENDPOINT1_H
