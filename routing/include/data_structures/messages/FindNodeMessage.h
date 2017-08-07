#pragma once
#include "data_structures/messages/Message.h"

#include <boost/uuid/uuid.hpp>
namespace m2 {
namespace routing {

using boost::uuids::uuid;

class FindNodeMessage : public Message
{
public:
    FindNodeMessage(NodeInfo node_info, uuid guid);
    ~FindNodeMessage();
};
}
}
