#include "handlers/FindDataHandler.h"

namespace m2 {
namespace routing {

FindDataHandler::FindDataHandler(Node& node):CommandHandler(node), NodeContainingObject(node)
{
}

FindDataHandler::~FindDataHandler()
{
}

void FindDataHandler::handleMessage(Message & message)
{
    assert(MessageType::FindDataRequest == message.message_type);
    FindDataRequestMessage casted_message = dynamic_cast<FindDataRequestMessage&>(message);
    UserInfo user_info = node.dht.get(casted_message.guid);
    FindDataResponseMessage response_message(
        node.self_info,
        casted_message.request_id,
        user_info,
        node.kbuckets_manager.getNeighbours(casted_message.guid));

    node.network_connector.sendMessage(
        casted_message.node_info.ip,
        casted_message.node_info.port,
        MessageBuilder::serialize(response_message));
    
}
        
} // namespace routing
} // namespace m2