#include "handlers/FindNodeHandler.h"

namespace m2 {
namespace routing {

FindNodeHandler::FindNodeHandler(Node& node):CommandHandler(node), NodeContainingObject(node)
{
}

FindNodeHandler::~FindNodeHandler()
{
}

void FindNodeHandler::handleMessage(Message& message)
{
    assert(MessageType::FindNodeRequest == message.message_type);
    FindNodeRequestMessage casted_message = dynamic_cast<FindNodeRequestMessage&>(message);
    std::list<NodeInfo> neighbours = node.kbuckets_manager.getNeighbours(casted_message.guid);
    FindNodeResponseMessage response_message(node.self_info, casted_message.request_id, neighbours);
    node.network_connector.sendMessage(
        casted_message.node_info.ip,
        casted_message.node_info.port,
        MessageBuilder::serialize(response_message));
}

} // namespace routing
} // namespace m2
