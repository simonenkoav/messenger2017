#include "processors/FindNodeProcessor.h"
#include <cassert>

namespace m2 {
namespace routing {
FindNodeProcessor::FindNodeProcessor(Node & node, uuid request_id) : FindProcessor(node, request_id)
{
}

void FindNodeProcessor::handleMessage(Message& message)
{
    assert(MessageType::FindNodeResponse == message.message_type);
    FindNodeResponseMessage casted_message = dynamic_cast<FindNodeResponseMessage&>(message);
    onNodeResponse(casted_message.node_info.uuid);
    receiveNodesVector(casted_message.found_nodes_info);
    askNext();
}

vector<char> FindNodeProcessor::getMessage()
{
    return MessageBuilder::serialize(FindNodeRequestMessage(node.self_info, searched_guid));
}

void FindNodeProcessor::onSearchFinsihed()
{
    completed = true;
    list<NodeInfo> answer;
    auto best = k_best.getBest();
    for (auto item : best) {
        answer.push_back(item->node_info);
    }
    result = new FindNodeResponseMessage(node.self_info, answer);
}

uuid getGuid(Message& message) {
    assert(MessageType::FindNodeRequest == message.message_type);
    FindNodeRequestMessage casted_message = dynamic_cast<FindNodeRequestMessage&>(message);
    return casted_message.guid;
}

}
}
