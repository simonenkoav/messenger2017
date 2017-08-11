#include "processors/PingProcessor.h"


namespace m2 {
namespace routing {

PingProcessor::PingProcessor(Node & node, uuid request_id) : Processor(node, request_id)
{
}


PingProcessor::~PingProcessor()
{
}

void PingProcessor::process(Message & message, OnRequestProcessed on_processed)
{
    assert(MessageType::PingRequest == message.message_type);
    callback = on_processed;
    // We can not use casted_message because its node_info contains addressee's info
    PingRequestMessage request_message(node.self_info, request_id);
    node.network_connector.sendMessage(
        message.node_info.ip,
        message.node_info.port,
        MessageBuilder::serialize(request_message));
    
    setTimeout(node.io_service, &PingProcessor::onTimeoutExpired, this);
}

void PingProcessor::handleMessage(Message& message)
{
    if (false == completed) {
        assert(MessageType::PingResponse == message.message_type);
        PingResponseMessage casted_message = dynamic_cast<PingResponseMessage&>(message);

        completed = true;
        callback(PingResponseMessage(casted_message));
    }
}
}

void PingProcessor::onTimeoutExpired()
{
    completed = true;
    //result = new NotRespondingMessage();
}

}
