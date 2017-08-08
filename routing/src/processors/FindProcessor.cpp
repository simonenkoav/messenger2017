#include "processors/FindProcessor.h"

namespace m2 {
namespace routing {
using namespace processors;

FindProcessor::FindProcessor(Node& node, uuid target) : Processor(node), k_best(Config::getK(), target)
{
    io.run();
}

void FindProcessor::process(uuid guid)
{
    clearSearchState();

    searched_guid = guid;
    list<NodeInfo> original_neighbours = node.kbuckets_manager.getNeighbours(searched_guid);
    for (auto item : original_neighbours) {
        NodeSearchStruct new_node_search(item);
        sorted_nodes.push_back(new_node_search);
        search_map[new_node_search.node_info.uuid] = &new_node_search;
    }
    askNext();
}

void FindProcessor::sendRequest(NodeSearchStruct* addressee)
{
    Message message = getMessage();
    node.network_connector.sendMessage(
        addressee->node_info.ip,
        addressee->node_info.port,
        MessageBuilder::serialize(message));
    auto timer = new boost::asio::deadline_timer(io, Config::getResponseTimeout());
    timer->async_wait(boost::bind(&FindProcessor::timeoutExpires, this, addressee->node_info.uuid, timer));
}

void FindProcessor::timeoutExpires(uuid guid, boost::asio::deadline_timer* expired_timer)
{
    delete expired_timer;
    auto it = search_map.find(guid);
    if (search_map.end() != it) {
        NodeSearchStruct* not_responding_node = it->second;
        if (NodeSearchStruct::state_type::wait_for_responce == not_responding_node->state) {
            not_responding_node->state = NodeSearchStruct::state_type::not_asked;
            //removeFromKBest(not_responding_node);
            k_best.deleteItem(not_responding_node->node_info.uuid);
            selectNewForKBest();
            askNext(1);
        }
    }
}

void FindProcessor::clearSearchState()
{
    k_best.clear();
    search_map.clear();
    sorted_nodes.clear();
}

void FindProcessor::selectNewForKBest()
{
    int need_to_select = Config::getK() - k_best.size();
    need_to_select = (0 > need_to_select) ? 0 : need_to_select;

    if (0 < need_to_select) {
        int already_added = 0;
        for (auto item : sorted_nodes) {
            if (NodeSearchStruct::not_asked == item.state ||
                NodeSearchStruct::responded == item.state) {
                if (false == k_best.contains(item.node_info.uuid)) {
                    // item is NOT already in k_best
                    already_added += (k_best.insert(&item)) ? 1 : 0;
                    if (already_added >= need_to_select) {
                        break;
                    }
                }
            }
        }
    }
}

void FindProcessor::askNext(int number)
{
    number = (0 >= number) ? Config::getAlpha() : number;

    list<NodeSearchStruct*> to_ask = k_best.getItemsToAsk(number);

    for (auto item : to_ask) {
        sendRequest(item);
    }
}

}
}
