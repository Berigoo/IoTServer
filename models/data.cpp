//
// Created by pach on 4/17/24.
//

#include "data.h"

bool data::isUuidExist(std::string uuid) {
    try{
        sql::ResultSet* res = DB::execPreparedQuery("SELECT COUNT(1) FROM data WHERE uuid=?", {uuid});
        if(res->next()){
            int count = res->getInt(1);
            if(count > 0){
                return true;
            } else{
                return false;
            }
        }else return false;
    }catch (sql::SQLException& e){
        return false;
    }
}
