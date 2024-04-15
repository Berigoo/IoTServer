cmake_minimum_required(VERSION 3.25)
project(IoTServer)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)
find_package(OpenSSL REQUIRED)

add_executable(IoTServer main.cpp utils/ssl.cpp utils/ssl.h utils/jsonReader.cpp utils/jsonReader.h utils/jsonWriter.cpp utils/jsonWriter.h routes/dataRoutes.cpp routes/dataRoutes.h routes/deviceRoutes.cpp routes/deviceRoutes.h)

target_link_libraries(IoTServer jsoncpp_lib ${OPENSSL_LIBRARIES})

