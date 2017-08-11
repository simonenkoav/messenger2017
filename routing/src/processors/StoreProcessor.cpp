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
    StoreRequestMessage casted_message = dynamic_cast<StoreRequestMessage&>(message);
    // We can not use casted_message because its node_info contains addressee's info
    StoreRequestMessage request_message(node.self_info, request_id, casted_message.user_info);
    node.network_connector.sendMessage(
        message.node_info.ip,
        message.node_info.port,
        MessageBuilder::serialize(request_message));
    // TODO: we can use here timer to set a timeout for response and return null message in case of no response
}

void StoreProcessor::handleMessage(Message& message)
{
    if (false == completed) {
        assert(MessageType::StoreResponse == message.message_type);
        StoreResponseMessage casted_message = dynamic_cast<StoreResponseMessage&>(message);

        completed = true;
        callback(StoreResponseMessage(casted_message));
    }
}
}
}
