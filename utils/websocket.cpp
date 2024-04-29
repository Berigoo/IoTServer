//
// Created by pach on 4/22/24.
//

#include "websocket.h"

std::map<string, server::connection_ptr> websocket::wsConnections;

websocket::websocket() {

}

websocket::~websocket() {

}

void websocket::onHttp(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);
    std::string reqBody = con->get_request_body();

    std::stringstream ss;
    ss << "got HTTP request with " << reqBody.size() << " bytes of body data.";

    con->set_body(ss.str());
    con->set_status(websocketpp::http::status_code::ok);
}

void websocket::onFail(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);

    std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message()  << std::endl;
}

void websocket::onClose(websocketpp::connection_hdl hdl) {
    std::cout << "Close handler" << std::endl;
}

void websocket::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;
}

bool websocket::validate(websocketpp::connection_hdl hdl) {
    std::cout << "Validation";
    return true;
}

void websocket::onOpen(websocketpp::connection_hdl hdl) {
    std::cout << "Open Handler" << std::endl;
}

void websocket::run(int port) {
    try {
//        svr.set_access_channels(websocketpp::log::alevel::all);
//        svr.clear_access_channels(websocketpp::log::alevel::frame_payload);

        svr.init_asio();
        svr.set_reuse_addr(true);

        svr.set_validate_handler(bind(&websocket::validate, this, ::_1));
        svr.set_http_handler(bind(&websocket::onHttp, this, ::_1));
        svr.set_fail_handler(bind(&websocket::onFail, this, ::_1));
        svr.set_close_handler(bind(&websocket::onClose, this, ::_1));
        svr.set_message_handler(bind(&websocket::onMessage, this, ::_1, ::_2));
        svr.set_open_handler(bind(&websocket::onOpen, this, ::_1));

        svr.listen(port);

        // Start the server accept loop
        svr.start_accept();

        // Start the ASIO io_service run loop
        svr.run();
    } catch (websocketpp::exception const & e) {
        std::cout << e.what() << std::endl;
    } catch (...) {
        std::cout << "other exception" << std::endl;
    }
}

// TODO it is N
bool websocket::isConnectionExist(server::connection_ptr conn_ptr) {
    for(auto i=wsConnections.begin(); i!=wsConnections.end(); i++){
        if(i->second == conn_ptr){
            return true;
        }
    }
    return false;
}

void websocket::closeAllEstablishedConns() {
    for (const auto& x:wsConnections) {
        std::string reason = "endpoint or server is going away!!!";
        x.second->close(websocketpp::close::status::going_away, reason);
    }
}

bool websocket::isUuidExist(string uuid) {
    for(auto i=wsConnections.begin(); i!=wsConnections.end(); i++){
        if(i->first == uuid){
            return true;
        }
    }
    return false;
}


//websocket::~websocket() = default;

