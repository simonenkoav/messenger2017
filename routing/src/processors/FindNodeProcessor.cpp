#include "processors/FindNodeProcessor.h"

using namespace m2::routing;

void FindNodeProcessor::process(uuid guid)
{
}

void FindNodeProcessor::sendRequest(NodeInfo recipient)
{
    FindNodeMessage message(node.self_info, searched_guid);
    node.networkConnector.sendMessage();
}