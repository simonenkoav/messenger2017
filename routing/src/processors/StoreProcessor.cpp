#include "processors/StoreProcessor.h"


namespace m2 {
namespace routing {

StoreProcessor::StoreProcessor(Node & node, uuid request_id) : Processor(node, request_id)
{
}

StoreProcessor::~StoreProcessor()
{
}

void StoreProcessor::process(Message & message, OnRequestProcessed on_processed)
{
    assert(MessageType::StoreRequest == message.message_type);
    callback = on_processed;
    StoreRequestMessage casted_message = dynamic_cast<const StoreRequestMessage&>(message);
    // We can not use casted_message because its node_info contains addressee's info
    StoreRequestMessage request_message(node.self_info, request_id, casted_message.user_info);
    node.network_connector.sendMessage(
        message.node_info.ip,
        message.node_info.port,
        MessageBuilder::serialize(request_message));

    setTimeout(node.io_service);
}

void StoreProcessor::handleMessage(const Message& message)
{
    if (false == completed) {
        assert(MessageType::StoreResponse == message.message_type);
        StoreResponseMessage casted_message = dynamic_cast<const StoreResponseMessage&>(message);

        completed = true;
        callback(StoreResponseMessage(casted_message));
    }
}

void StoreProcessor::onTimeoutExpired()
{
    completed = true;
    callback(NotRespondingMessage(NodeInfo(), request_id));
}

}
}
