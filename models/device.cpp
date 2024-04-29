//
// Created by pach on 4/15/24.
//

#include "device.h"

device::device(std::string uuid, std::string name, deviceType type, int owner) {
    this->uuid = uuid;
    this->name = name;
    this->type = type;
    this->owner = owner;
}

std::string device::getUuid() {
    return this->uuid;
}

std::string device::getName() {
    return this->name;
}

deviceType device::getType() {
    return this->type;
}

device device::getDeviceById(int id) {
    return device(0, "da", DIGITAL_1_OUTPUT, -1);
}

bool device::addDevice(const device &dev) {
    try {
            // check if uuid available
        sql::ResultSet* res = DB::execPreparedQuery("SELECT * FROM devices WHERE uuid=?", {dev.uuid});
        if(!res->next()) {
            DB::execPreparedQuery("INSERT INTO devices VALUES(?, ?, ?, ?)",
                                  {dev.uuid, dev.name, to_string(dev.type),
                                         to_string(dev.owner)});
            return true;
        }else {
            return false;
        }
    }catch (sql::SQLException& e){
        std::cerr << "Error inserting data, " << e.what() << '\n';
    }
}

void device::removeDeviceById(int id) {

}

std::vector<device> device::getAllDevice() {
    return std::vector<device>();
}

void device::setUuid(std::string uuid) {
    this->uuid = uuid;
}

bool device::isUuidExist(std::string uuid) {
    try{
        sql::ResultSet* res = DB::execPreparedQuery("SELECT COUNT(1) FROM devices WHERE uuid=?", {uuid});
        if(res->next()){
            int count = res->getInt(1);
            if(count > 0){
                return true;
            } else{
                return false;
            }
        }else return false;
    }catch (sql::SQLException& e){
        std::cout << "Failed to validate device uuid, " << e.what() << '\n';
        return false;
    }
}
