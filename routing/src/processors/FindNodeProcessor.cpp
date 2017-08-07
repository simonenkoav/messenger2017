#include "processors/FindNodeProcessor.h"

namespace m2 {
namespace routing {
FindNodeProcessor::FindNodeProcessor(Node & node) : FindProcessor(node)
{
}

void FindNodeProcessor::process(uuid guid)
{
}

void FindNodeProcessor::sendRequest(NodeInfo recipient)
{
    FindNodeRequestMessage message(node.self_info, searched_guid);
    node.network_connector.sendMessage(recipient.ip, recipient.port, MessageBuilder::serialize(message));
}
}
}