#pragma once
#include "data_structures/NodeInfo.h"

namespace m2 {
namespace routing {



class Message
{
public:
    Message(NodeInfo node_info);
    ~Message();
};
    
} // namespace routing
} // namespace m2