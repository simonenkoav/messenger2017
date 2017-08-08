#include "processors/FindDataProcessor.h"

using namespace m2::routing;


FindDataProcessor::FindDataProcessor(Node & node, uuid request_id, uuid target) :
    FindProcessor(node, request_id, target), CommandHandler(node)
{
}

void FindDataProcessor::handleMessage(Message & message)
{
    assert(MessageType::FindDataResponse == message.message_type);
    FindDataResponseMessage casted_message = dynamic_cast<FindDataResponseMessage&>(message);
    if (casted_message.)
    onNodeResponse(casted_message.node_info.uuid);
    receiveNodesVector(casted_message.found_nodes_info);
    askNext();
}

vector<char> FindDataProcessor::getMessage()
{
    return MessageBuilder::serialize(FindDataRequestMessage(node.self_info, searched_guid));
}

void FindDataProcessor::onSearchFinsihed()
{
    // TODO: implement callback call to send result
}
