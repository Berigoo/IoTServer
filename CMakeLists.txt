cmake_minimum_required(VERSION 3.25)
project(IoTServer)

set(CMAKE_CXX_STANDARD 17)

find_package(jsoncpp REQUIRED)
find_package(OpenSSL REQUIRED)

include_directories(SYSTEM "/usr/local/include/mariadb")
link_directories("/usr/local/lib/mariadb")
add_library(mariadbcpp STATIC IMPORTED)
set_property(TARGET mariadbcpp PROPERTY IMPORTED_LOCATION "/usr/local/lib/mariadb/libmariadbcpp.so")

add_executable(IoTServer main.cpp utils/ssl.cpp utils/ssl.h utils/jsonReader.cpp utils/jsonReader.h utils/jsonWriter.cpp utils/jsonWriter.h routes/dataRoutes.cpp routes/dataRoutes.h routes/deviceRoutes.cpp routes/deviceRoutes.h models/device.h models/device.cpp utils/databaseHolder.cpp utils/databaseHolder.h models/DBdevice.cpp models/DBdevice.h)

target_link_libraries(IoTServer jsoncpp_lib ${OPENSSL_LIBRARIES} mariadbcpp)

