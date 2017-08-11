#include "data_structures/NodeInfo.h"


namespace m2 {
namespace routing {



    NodeInfo::NodeInfo(boost::uuids::uuid uuid, std::string ip, int port)
            : uuid(uuid), ip(ip), port(port) {}


    NodeInfo::~NodeInfo() {
    }

    NodeInfo::NodeInfo() {

    }

}
}
