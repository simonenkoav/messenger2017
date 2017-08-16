#include "processors/FindNodeProcessor.h"
#include <cassert>

namespace m2 {
namespace routing {
FindNodeProcessor::FindNodeProcessor(Node & node, uuid request_id) : FindProcessor(node, request_id)
{
}

void FindNodeProcessor::handleMessage(const Message& message)
{
    if (false == completed) {
        assert(MessageType::FindNodeResponse == message.message_type);
        FindNodeResponseMessage casted_message = dynamic_cast<const FindNodeResponseMessage&>(message);
        onNodeResponse(casted_message.node_info.guid);
        receiveNodesList(casted_message.nodes_info);
        size_t asked = askNext();
        if (0 == asked) {
            if (doesSearchFinished()) {
                onSearchFinsihed();
            }
        }
    }
}

vector<char> FindNodeProcessor::getMessage()
{
    return MessageBuilder::serialize(FindNodeRequestMessage(node.self_info, request_id, searched_guid));
}

void FindNodeProcessor::onSearchFinsihed()
{
    completed = true;
    list<NodeInfo> answer;
    auto best = k_best.getBest();
    for (auto item : best) {
        answer.push_back(item->node_info);
    }
    result = new FindNodeResponseMessage(node.self_info, request_id, answer);
}

uuid getGuid(Message& message) {
    assert(MessageType::FindNodeRequest == message.message_type);
    FindNodeRequestMessage casted_message = dynamic_cast<const FindNodeRequestMessage&>(message);
    return casted_message.guid;
}

}
}
