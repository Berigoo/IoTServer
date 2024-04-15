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
    res.set_content("Hello World!", "text/plain");
}

void deviceRoutes::removeDevices(const httplib::Request &req, httplib::Response &res) {
}

void deviceRoutes::addDevices(const httplib::Request &req, httplib::Response &res) {
}
