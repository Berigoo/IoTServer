//
// Created by pach on 4/14/24.
//

#ifndef IOTSERVER_JSONREADER_H
#define IOTSERVER_JSONREADER_H

#include "json/json.h"
#include "fstream"
#include "exception"

class jsonReader {
public:
    Json::Value value;


public:
    jsonReader(const char* filename);
};


#endif //IOTSERVER_JSONREADER_H
