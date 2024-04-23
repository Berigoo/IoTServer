//
// Created by pach on 4/22/24.
//

#include "ws.h"

ws::ws() {
    try {
        svr.set_access_channels(websocketpp::log::alevel::all);
        svr.clear_access_channels(websocketpp::log::alevel::frame_payload);

        svr.init_asio();
        svr.set_reuse_addr(true);

        svr.set_validate_handler(bind(&ws::validate, this, _1));
        svr.set_http_handler(bind(&ws::onHttp, this, _1));
        svr.set_fail_handler(bind(&ws::onFail, this, _1));
        svr.set_close_handler(bind(&ws::onClose, this, _1));
        svr.set_message_handler(bind(&ws::onMessage, this, _1, _2));
        svr.set_open_handler(bind(&ws::onOpen, this, _1));
    }catch (websocketpp::exception const& e){
        std::cout << e.what() << '\n';
    }
}

void ws::onHttp(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);

    std::string res = con->get_request_body();

    std::stringstream ss;
    ss << "got HTTP request with " << res.size() << " bytes of body data.";

    con->set_body(ss.str());
    con->set_status(websocketpp::http::status_code::ok);
}

void ws::onFail(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);

    std::cout << "Fail handler: " << con->get_ec() << " " << con->get_ec().message()  << std::endl;
}

void ws::onClose(websocketpp::connection_hdl hdl) {
    std::cout << "Close handler" << std::endl;
}

void ws::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    std::cout << "on_message called with hdl: " << hdl.lock().get()
              << " and message: " << msg->get_payload()
              << std::endl;
}

bool ws::validate(websocketpp::connection_hdl hdl) {
    return true;
}

void ws::onOpen(websocketpp::connection_hdl hdl) {
    std::cout << "Open Handler" << std::endl;
}

void ws::run(int port) {
    try {
        svr.listen(port);
        svr.start_accept();

        svr.run();
    }catch (websocketpp::exception const& e){
        std::cout << e.what() << '\n';
    }
}

