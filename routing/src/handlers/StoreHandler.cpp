#include "handlers/StoreHandler.h"


namespace m2 {
namespace routing {

StoreHandler::StoreHandler(Node& node): CommandHandler(node), NodeContainingObject(node)
{
}


StoreHandler::~StoreHandler()
{
}
void StoreHandler::handleMessage(Message & message)
{
    assert(MessageType::StoreRequest == message.message_type);
    StoreRequestMessage casted_message = dynamic_cast<StoreRequestMessage&>(message);
    node.dht.put(casted_message.user_info);
    StoreResponseMessage response_message(node.self_info, casted_message.request_id);
    node.network_connector.sendMessage(
        casted_message.node_info.ip,
        casted_message.node_info.port,
        MessageBuilder::serialize(response_message));

}
}
}
