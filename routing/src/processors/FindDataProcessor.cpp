#include "processors/FindDataProcessor.h"

using namespace m2::routing;


FindDataProcessor::FindDataProcessor(Node & node, uuid request_id) : FindProcessor(node, request_id)
{
}

void FindDataProcessor::handleMessage(Message & message)
{
    assert(MessageType::FindDataResponse == message.message_type);
    FindDataResponseMessage casted_message = dynamic_cast<FindDataResponseMessage&>(message);
    // TODO: choose what to do based on info in message userinfo or list of nodes
    //if (nullptr != casted_message.user_info) {
    //    result = new FindDataResponseMessage(node, casted_message.user_info);
    //    completed = true;
    //}
    //else
    //{
    //    onNodeResponse(casted_message.node_info.uuid);
    //    receiveNodesVector(casted_message.found_nodes_info);
    //    askNext();
    //}
}

vector<char> FindDataProcessor::getMessage()
{
    return MessageBuilder::serialize(FindDataRequestMessage(node.self_info, searched_guid));
}

uuid FindDataProcessor::getGuid(Message & message)
{
    assert(MessageType::FindDataRequest == message.message_type);
    FindDataRequestMessage casted_message = dynamic_cast<FindDataRequestMessage&>(message);
    return casted_message.guid;
}
