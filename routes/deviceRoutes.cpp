//
// Created by pach on 4/15/24.
//

#include "deviceRoutes.h"

deviceRoutes::deviceRoutes(httplib::SSLServer& server) {
    server.Post("/device/add", [&](const httplib::Request& req, httplib::Response& res){
        addDevices(req, res);
    });
    server.Post("/device/rm", [&](const httplib::Request& req, httplib::Response& res){
        removeDevices(req, res);
    });
    server.Get("/device/ls", [&](const httplib::Request& req, httplib::Response& res){
        listDevices(req, res);
    });
}



void deviceRoutes::listDevices(const httplib::Request &req, httplib::Response &res) {
    res.set_header("msg", "hellow");
    res.set_content("Hello World!", "text/plain");
}

void deviceRoutes::removeDevices(const httplib::Request &req, httplib::Response &res) {
    jsonReader data(&req.body);
    if(!(data.value.isMember("usernm") && data.value.isMember("passwd") && data.value.isMember("device_uuid"))){
        res.status = 422;
        return;
    }else{
        if(DBdevice::checkUserCredentials(data.value.get("usernm", " ").asString(), data.value.get("passwd", " ").asString())){
            try{
                // remove device entry if user valid
                DBdevice::execPreparedQuery("DELETE FROM devices WHERE uuid=?", {data.value.get("device_uuid", " ").asString()});
                res.status = 200;
                return;
            }catch (sql::SQLException& e){
                std::cout << "Failed to delete device entry, " << e.what() << '\n';
                res.status = 500;
                return;
            }
        }
    }
}

// usernm, passwd, device_type, device_name, owner
void deviceRoutes::addDevices(const httplib::Request &req, httplib::Response &res) {
    jsonReader data(&req.body);
    if(!(data.value.isMember("usernm") && data.value.isMember("passwd") && data.value.isMember("device_name") && data.value.isMember("device_type") && data.value.isMember("owner"))){
        res.status = 422;
        return;
    }else {
        try {
            sql::ResultSet *resQuery = DBdevice::execPreparedQuery(
                    "SELECT COUNT(id) FROM users WHERE username=? AND passwd=?",
                    {data.value.get("usernm", " ").asString(), data.value.get("passwd", " ").asString()});
            if (resQuery->next()) {
                int count = resQuery->getInt(1);
                if (count > 0) {
                    // generate uuid if user valid
                    boost::uuids::uuid uuid = boost::uuids::random_generator()();
                    device dev(boost::uuids::to_string(uuid), data.value.get("device_name", " ").asString(),
                               static_cast<deviceType>(data.value.get("device_type", -1).asInt()),
                               data.value.get("owner", -1).asInt());
                    while (!device::addDevice(dev)) {
                        uuid = boost::uuids::random_generator()();
                        dev.setUuid(boost::uuids::to_string(uuid));
                    }
                    std::cout << "Adding device \n";
                    res.set_header("uuid", boost::uuids::to_string(uuid));
                } else {
                    std::cout << "Users not found \n";
                }
            }
            res.status = 200;
            return;
        } catch (sql::SQLException &e) {
            std::cerr << "Failed adding new devices, " << e.what() << '\n';
            res.status = 500;
            return;
        }
    }
}
