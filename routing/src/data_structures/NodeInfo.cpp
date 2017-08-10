#include "data_structures/NodeInfo.h"


NodeInfo::NodeInfo(boost::uuids::uuid uuid, std::string ip, int port)
  : uuid(uuid), ip(ip), port(port) {}


NodeInfo::~NodeInfo()
{
}
