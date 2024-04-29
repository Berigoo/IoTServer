//
// Created by pach on 4/23/24.
//

#include "wsEndpoint1.h"

void wsEndpoint1::onOpen(websocketpp::connection_hdl hdl) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);
    std::string uuid = con->get_request_header("uuid");

    std::cout << "[ON OPEN] uuid: " << uuid << '\n';

    if (!isConnectionExist(con)) {
        // if not exist then insert it, if the uuid fullfill
        std::cout << "[ON OPEN] Checking uuid" << '\n';
        if (!uuid.empty()) {
            if (device::isUuidExist(uuid)) {
                websocket::wsConnections.insert({uuid, con});
            } else {
                con->close(websocketpp::close::status::normal, "invalid uuid");
            }
        } else {
            con->close(websocketpp::close::status::normal, "unprocessable content");
        }
    }
}

void wsEndpoint1::onMessage(websocketpp::connection_hdl hdl, message_ptr msg) {
    server::connection_ptr con = svr.get_con_from_hdl(hdl);
    jsonReader data(&msg->get_payload());

    std::string leftuuid;

    // get sender uuid
    for(auto i=wsConnections.begin(); i!=wsConnections.end(); i++){
        if(i->second == con){
            leftuuid = i->first;
            break;
        }
    }

    std::cout << leftuuid << '\n';

    try{
        // get paired uuid
        sql::ResultSet* res = DB::getRightUUID(leftuuid);
        // loop through paired uuid and send signal to every of it
        while(res->next()){
            sql::SQLString rightuuid =  res->getString("uuid");
            std::cout << res->getString(1) << '\n';

            // parsing json
            Json::Value jsonVal;
            string tmp = "data0";
            int i=0;
            while(data.value.isMember(tmp)){
                jsonVal[tmp] = data.value.get(tmp, "null").asInt();
                i++;
                tmp = "data" + to_string(i);
            }
            jsonWriter writeJson(jsonVal);

            // check  device is online
            if(websocket::isUuidExist(rightuuid.c_str()))
                wsConnections[rightuuid.c_str()]->send(*writeJson.writeToString());
        }
    }catch (sql::SQLException& e){
        std::cout <<  e.what() << '\n';
    }
}
