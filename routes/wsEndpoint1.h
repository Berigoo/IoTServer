//
// Created by pach on 4/23/24.
//

#ifndef IOTSERVER_WSROUTES_H
#define IOTSERVER_WSROUTES_H

#include "../utils/websocket.h"

class wsRoutes : public websocket{
    void onOpen(websocketpp::connection_hdl hdl) override;
};


#endif //IOTSERVER_WSROUTES_H
