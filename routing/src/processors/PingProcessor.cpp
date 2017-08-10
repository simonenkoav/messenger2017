#include "processors/PingProcessor.h"


namespace m2 {
namespace routing {

PingProcessor::PingProcessor(Node & node, uuid request_id) : Processor(node, request_id)
{
}


PingProcessor::~PingProcessor()
{
}

void PingProcessor::process(Message & message)
{
    assert(MessageType::PingRequest == message.message_type);
    // We can not use casted_message because its node_info contains addressee's info
    PingRequestMessage request_message(node.self_info);
    node.network_connector.sendMessage(
        message.node_info.ip,
        message.node_info.port,
        MessageBuilder::serialize(request_message));
    // TODO: we can use here timer to set a timeout for response and return null message in case of no response
}

void PingProcessor::handleMessage(Message& message)
{
    assert(MessageType::PingResponse == message.message_type);
    PingResponseMessage casted_message = dynamic_cast<PingResponseMessage&>(message);

    completed = true;
    result = new PingResponseMessage(casted_message);
}
}
}