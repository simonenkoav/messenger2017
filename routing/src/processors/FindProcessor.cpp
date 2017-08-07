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
    not_asked = node.kbuckets_manager.getNeighbours(searched_guid);
    int alpha = Config::getAlpha();
    alpha = (not_asked.size() < alpha) ? not_asked.size() : alpha;
    for (size_t i = 0; i < alpha; i++)
    {
        sendRequest(not_asked.front());
        auto front = not_asked.front();
        wait_for_answer.push_back(front);
        not_asked.pop_front();
    }
}

}
}
