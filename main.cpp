#define CPPHTTPLIB_OPENSSL_SUPPORT
#include <httplib.h>
#include "utils/ssl.h"
#include "utils/jsonReader.h"
#include "utils/jsonWriter.h"
#include "routes/deviceRoutes.h"

int main(){
    jsonReader config("../config.json");

    ssl server(config.value.get("sslCert", "cert.pem").asCString(), config.value.get("sslKey", "cert.key").asCString());

    Json::Value data;
    data["Hello"] = "World";
    data["world"] = 2;

    jsonWriter json(data);

    server.Get("/", [&](const httplib::Request& req, httplib::Response& res){
        res.set_content(*json.writeToString(), "application/json");
    });

    deviceRoutes deviceRoute(server);

    server.listen(config.value.get("serverHost", "0.0.0.0").asCString(), config.value.get("serverPort", 80).asInt());

    return 0;
}