#include "handlers/PingHandler.h"

namespace m2 {
namespace routing {

PingHandler::PingHandler(Node& node) : CommandHandler(node), NodeContainingObject(node)
{
}


PingHandler::~PingHandler()
{
}

void PingHandler::handleMessage(Message & message)
{
    assert(MessageType::PingRequest == message.message_type);
    PingRequestMessage casted_message = dynamic_cast<PingRequestMessage&>(message);
    PingResponseMessage response_message(node.self_info);
    node.network_connector.sendMessage(
        casted_message.node_info.ip,
        casted_message.node_info.port,
        MessageBuilder::serialize(response_message));
}

}
}