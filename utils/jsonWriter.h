//
// Created by pach on 4/15/24.
//

#ifndef IOTSERVER_JSONWRITER_H
#define IOTSERVER_JSONWRITER_H

#include "map"
#include "string"
#include "json/json.h"

//class anyBase{
//public:
//    virtual ~anyBase() = 0;
//};
//inline anyBase::~anyBase() {};
//
//template <class T>
//class any : public anyBase{
//public:
//    T data;
//    explicit any(const T& data){ this->data = data; }
//};

class jsonWriter {
public:
    Json::Value jsonRoot;
    jsonWriter(Json::Value& data);

    const std::string* writeToString();
};


#endif //IOTSERVER_JSONWRITER_H
