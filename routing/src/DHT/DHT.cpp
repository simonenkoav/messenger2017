//
// Created by ovv on 05.08.17.
//

#include "DHT/DHT.h"


using namespace m2::routing;


void DHT::put(UserInfo new_info)
{
    map.insert(std::make_pair(new_info.uuid, new_info));
}


void DHT::erase(uuid key)
{
    map.erase(key);
}


UserInfo DHT::get(uuid key)
{
    auto founded = map.find(key);
    if (founded != map.end()) {
        return founded->second;
    } else {
        return UserInfo();
    }
}