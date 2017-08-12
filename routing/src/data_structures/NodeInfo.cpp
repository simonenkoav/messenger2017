#include "data_structures/NodeInfo.h"


namespace m2 {
namespace routing {

NodeInfo::NodeInfo(boost::uuids::uuid guid, std::string ip, int port)
        : guid(guid), ip(ip), port(port) {}


NodeInfo::~NodeInfo() {
}

NodeInfo::NodeInfo() {

}

}
}
