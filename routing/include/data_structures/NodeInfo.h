#pragma once
#include <string>
#include <boost/uuid/uuid.hpp>

namespace m2 {
namespace routing {

struct NodeInfo
{
    boost::uuids::uuid guid;
    std::string ip;
    int port;

    NodeInfo();
    NodeInfo(boost::uuids::uuid guid, std::string ip, int port);

    virtual ~NodeInfo();

    friend bool operator==(const NodeInfo &first, const NodeInfo &second) {
        return first.guid == second.guid;
    };
};

} // namespace routing
} // namespace m2
