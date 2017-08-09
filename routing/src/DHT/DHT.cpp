//
// Created by ovv on 05.08.17.
//

#include "DHT/DHT.h"


using namespace m2::routing;

void DHT::put(NodeInfo new_info)
{
    map.insert(std::make_pair(new_info.uuid, new_info));
}

void DHT::erase(uuid key)
{
    map.erase(key);
}

bool DHT::get(uuid key, NodeInfo& result)
{
    auto founded = map.find(key);
    if (founded != map.end()) {
        result = founded->second;
        return true;
    } else {
        return false;
    }
}