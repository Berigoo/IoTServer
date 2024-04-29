//
// Created by pach on 4/15/24.
//

#include "dataRoutes.h"

dataRoutes::dataRoutes(httplib::SSLServer &server) {
    server.Post("/device/data/send", [&](const httplib::Request& req, httplib::Response& res){
        dataSend(req, res);
    });
}

void dataRoutes::dataSend(const httplib::Request &req, httplib::Response &res) {
    jsonReader data(&req.body);
    std::cout << req.body << '\n';
    if(!(data.value.isMember("device_uuid") && data.value.isMember("data0"))){
        res.status = 422;
        return;
    }else{
        if(device::isUuidExist(data.value.get("device_uuid", " ").asString())){
            try{
                Json::Value deviceValue;
                std::string tmp = "data0";
                int i=0;
                while(data.value.isMember(tmp)){
                    deviceValue[tmp] = data.value.get(tmp, " ").asString();
                    i++;
                    tmp = "data" + to_string(i);
                }
                jsonWriter writer(deviceValue);

                if(data::isUuidExist(data.value.get("device_uuid", " ").asString())) {
                    DB::execPreparedQuery("UPDATE data SET value=? WHERE uuid=?",
                                          {*writer.writeToString(),
                                           data.value.get("device_uuid", " ").asString()});
                } else {
                    DB::execPreparedQuery("INSERT INTO data VALUES(NULL, ?, ?)",
                                          {data.value.get("device_uuid", " ").asString(), *writer.writeToString()});
                }
                res.status = 200;
            }catch (sql::SQLException& e){
                std::cout << "Failed to update device data value, " << e.what() << '\n';
                res.status = 500;
                return;
            }
        }else{
            std::cout << "Invalid UUID" << '\n';
        }
    }
}
