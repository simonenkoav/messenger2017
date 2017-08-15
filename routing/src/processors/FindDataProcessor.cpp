#include "processors/FindDataProcessor.h"

namespace m2 {
namespace routing {
FindDataProcessor::FindDataProcessor(Node & node, uuid request_id) : FindProcessor(node, request_id)
{
}

void FindDataProcessor::handleMessage(const Message & message)
{
    assert(MessageType::FindDataResponse == message.message_type);
    FindDataResponseMessage casted_message = dynamic_cast<const FindDataResponseMessage&>(message);
    //TODO: choose what to do based on info in message userinfo or list of nodes
    if (casted_message.user_info.isNil()) {
        onNodeResponse(casted_message.node_info.guid);
        receiveNodesList(casted_message.nodes_info);
        askNext();
    }
    else
    {
        completed = true;
        callback(FindDataResponseMessage(casted_message));
    }
}

vector<char> FindDataProcessor::getMessage()
{
    return MessageBuilder::serialize(FindDataRequestMessage(node.self_info, request_id, searched_guid));
}

void FindDataProcessor::onSearchFinsihed()
{
    completed = true;
    callback(NotFoundMessage(NodeInfo(), request_id, searched_guid));
}

uuid FindDataProcessor::getGuid(Message & message)
{
    assert(MessageType::FindDataRequest == message.message_type);
    FindDataRequestMessage casted_message = dynamic_cast<const FindDataRequestMessage&>(message);
    return casted_message.guid;
}
}
}