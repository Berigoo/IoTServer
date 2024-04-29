#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include "utils/ssl.h"
#include "utils/jsonReader.h"
#include "utils/jsonWriter.h"
#include "routes/deviceRoutes.h"
#include "routes/dataRoutes.h"
#include "routes/wsEndpoint1.h"
#include "thread"

jsonReader config("../config.json");
ssl httpServer(config.value.get("sslCert", "cert.pem").asCString(), config.value.get("sslKey", "cert.key").asCString());

int main(){
    Json::Value data;
    data["Hello"] = "World";
    data["world"] = 2;

    jsonWriter json(data);

    httpServer.Get("/", [&](const httplib::Request& req, httplib::Response& res){
        res.set_content(*json.writeToString(), "application/json");
    });

    deviceRoutes deviceRoute(httpServer);
    dataRoutes dataRoute(httpServer);
    wsEndpoint1 websocketEndpoint;

    std::thread websocketThread(&websocket::run, &websocketEndpoint, config.value.get("wsPort", 80).asInt());
    httpServer.listen(config.value.get("serverHost", "0.0.0.0").asCString(), config.value.get("serverPort", 80).asInt());

    websocketThread.join();
    wsEndpoint1::closeAllEstablishedConns();
    websocketEndpoint.svr.stop_listening();
    return 0;
}