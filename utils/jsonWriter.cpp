//
// Created by pach on 4/15/24.
//

#include "jsonWriter.h"

jsonWriter::jsonWriter(Json::Value& data) {
    jsonRoot = data;
}

const std::string* jsonWriter::writeToString() {
    Json::StreamWriterBuilder builder;
    const std::string* jsonString = new const std::string (Json::writeString(builder, jsonRoot));
    return jsonString;
}
