#include "processors/FindProcessor.h"

namespace m2 {
namespace routing {
FindProcessor::FindProcessor(Node& node) : node(node)
{
}

Message * FindProcessor::handleMessage(Message message)
{
    return nullptr;
}

void FindProcessor::process(uuid guid)
{
    searched_guid = guid;
    //not_asked = node.kbucketsManager.getNeighbours(searched_guid);
    int alpha = Config::getAlpha();
    alpha = (not_asked.size() < alpha) ? not_asked.size() : alpha;
    for (size_t i = 0; i < alpha; i++)
    {
        sendRequest(not_asked.front());
        wait_for_answer.push_back(not_asked.front());
        not_asked.pop_front();
    }
}

void FindProcessor::sendRequest(NodeInfo recipient)
{

}
}
}
