//
// Created by ovv on 05.08.17.
//

#pragma once

#include <unordered_map>

#include "boost/functional/hash.hpp"
#include "boost/uuid/uuid.hpp"
#include <data_structures/NodeInfo.h>

namespace m2 {
namespace routing {

using boost::uuids::uuid;

class DHT
{
 public:
    DHT() = default;
    DHT(DHT&) = delete;

    void put(NodeInfo new_info);
    void erase(uuid key);
    bool get(uuid key, NodeInfo& result);

 private:
    std::unordered_map<uuid, NodeInfo, boost::hash<boost::uuids::uuid>> map;
};

} // end routing
} // end m2