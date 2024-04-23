//
// Created by pach on 4/23/24.
//

#include "wsRoutes.h"

void wsRoutes::onOpen(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);
    std::string uuid = con->get_request_header("uuid");

    if (!isConnectionExist(con)) {
        // if not exist then insert it, if the uuid fullfill
        std::cout << "Checking uuid" << '\n';
        if (!uuid.empty()) {
            if (device::isUuidExist(uuid)) {
                websocket::wsConnections.push_back(con);
            } else {
                con->close(websocketpp::close::status::normal, "invalid uuid");
                return;
            }
        } else {
            con->close(websocketpp::close::status::normal, "unprocessable content");
        }
    }
}
