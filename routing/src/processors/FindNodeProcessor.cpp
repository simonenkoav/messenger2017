#include "processors/FindNodeProcessor.h"

namespace m2 {
namespace routing {
FindNodeProcessor::FindNodeProcessor(Node & node, uuid target) : FindProcessor(node, target), CommandHandler(node)
{
}

void FindNodeProcessor::handleMessage(Message message)
{
    list<NodeInfo> original_neighbours = node.kbuckets_manager.getNeighbours(searched_guid);
    for (auto item : original_neighbours) {
        NodeSearchStruct new_node_search(item);
        sorted_nodes.push_back(new_node_search);
        search_map[new_node_search.node_info.uuid] = &new_node_search;
    }
    askNext();
}

Message FindNodeProcessor::getMessage()
{
    return FindNodeMessage (node.self_info, searched_guid);
}


}
}