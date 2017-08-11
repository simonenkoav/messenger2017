//
// Created by ovv on 05.08.17.
//

#pragma once

#include <unordered_map>

#include "boost/functional/hash.hpp"
#include "boost/uuid/uuid.hpp"
#include <data_structures/UserInfo.h>

namespace m2 {
namespace routing {

using boost::uuids::uuid;

class DHT
{
 public:
    DHT() = default;
    DHT(DHT&) = delete;

    void put(UserInfo new_info);
    void erase(uuid key);
    bool get(uuid key, UserInfo& result);

 private:
    std::unordered_map<uuid, UserInfo, boost::hash<boost::uuids::uuid>> map;
};

} // end routing
} // end m2