//
// Created by pach on 4/15/24.
//

#ifndef IOTSERVER_DEVICE_H
#define IOTSERVER_DEVICE_H

#include "string"
#include "vector"
#include "../utils/databaseHolder.h"
#include "../models/DB.h"

enum deviceType{
    UNDEFINED,
    DIGITAL_1_INPUT,
    DIGITAL_1_OUTPUT
};

class device {
public:
    device(std::string uuid, std::string name, deviceType type, int owner);

    std::string getUuid();
    std::string getName();
    deviceType getType();
    int getOwner();

    void setUuid(std::string uuid);

    static device getDeviceById(int id);
    static bool addDevice(const device& dev);
    static void removeDeviceById(int id);
    static std::vector<device> getAllDevice();

    static bool isUuidExist(std::string uuid);

private:
    std::string uuid;
    std::string name;
    deviceType type;
    int owner;
};


#endif //IOTSERVER_DEVICE_H
