#include "data_structures/messages/FindNodeMessage.h"

namespace m2 {
namespace routing {
FindNodeMessage::FindNodeMessage(NodeInfo node_info, uuid guid) :Message(node_info)
{

}


FindNodeMessage::~FindNodeMessage()
{
}

}
}
