#include "processors/FindNodeProcessor.h"
#include <cassert>

namespace m2 {
namespace routing {
FindNodeProcessor::FindNodeProcessor(Node & node, uuid target) : FindProcessor(node, target), CommandHandler(node)
{
}

void FindNodeProcessor::handleMessage(Message& message)
{
    assert(MessageType::FindNodeResponse == message.message_type);
    FindNodeResponseMessage casted_message = dynamic_cast<FindNodeResponseMessage&>(message);
    onNodeResponse(casted_message.node_info.uuid);
    receiveNodesVector(casted_message.found_nodes_info);
}

vector<char> FindNodeProcessor::getMessage()
{
    return MessageBuilder::serialize(FindNodeRequestMessage(node.self_info, searched_guid));
}


}
}
