//
// Created by pach on 4/14/24.
//

#include "jsonReader.h"

jsonReader::jsonReader(const char *filename) {
    std::ifstream ifs(filename);
    if(!ifs.is_open()){
        throw std::runtime_error("Failed to open jsonReader file");
    }

    Json::CharReaderBuilder builder;
    builder["collectComments"] = true;
    std::string err;
    if(!Json::parseFromStream(builder, ifs, &value, &err)){
        throw std::runtime_error("Failed to parse json");
    }
}
