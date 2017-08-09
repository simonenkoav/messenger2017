#include "processors/FindProcessor.h"

namespace m2 {
namespace routing {
using namespace processors;

std::function<boost::uuids::uuid(const NodeSearchStruct& node)> uuidGetter =
[](const NodeSearchStruct& node) -> boost::uuids::uuid {
    return node.node_info.uuid;
};

FindProcessor::FindProcessor(Node& node, uuid request_id ) : Processor(node, request_id), k_best(Config::getK())
{
}

void FindProcessor::process(Message& message)
{
    clearSearchState();
    searched_guid = getGuid(message);
    k_best.setTarget(searched_guid);
    list<NodeInfo> original_neighbours = node.kbuckets_manager.getNeighbours(searched_guid);
    for (auto item : original_neighbours) {
        addNode(item);
    }
    // TODO: make sorting of referenced list (list&) 
    KBucketsTools::sortByDist(sorted_nodes, searched_guid, uuidGetter);
    selectNewForKBest();
    askNext();
}

void FindProcessor::sendRequest(NodeSearchStruct* addressee)
{
    addressee->state = NodeSearchStruct::wait_for_response;
    node.network_connector.sendMessage(
        addressee->node_info.ip,
        addressee->node_info.port,
        getMessage());
    auto timer = new boost::asio::deadline_timer(node.io_service, Config::getResponseTimeout());
    timer->async_wait(boost::bind(&FindProcessor::timeoutExpires, this, addressee->node_info.uuid, timer));
}

void FindProcessor::timeoutExpires(uuid guid, boost::asio::deadline_timer* expired_timer)
{
    delete expired_timer;
    auto it = search_map.find(guid);
    if (search_map.end() != it) {
        NodeSearchStruct* not_responding_node = it->second;
        if (NodeSearchStruct::state_type::wait_for_response == not_responding_node->state) {
            not_responding_node->state = NodeSearchStruct::state_type::not_responding;
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

void FindProcessor::addNode(NodeInfo node_info)
{
    NodeSearchStruct new_node_search(node_info);
    sorted_nodes.push_back(new_node_search);
    search_map[new_node_search.node_info.uuid] = &new_node_search;
    k_best.insert(&new_node_search); // here we try to insert (perhaps failed to insert)
}

void FindProcessor::askNext(int number)
{
    number = (0 >= number) ? Config::getAlpha() : number;

    list<NodeSearchStruct*> to_ask = k_best.getItemsToAsk(number);

    for (auto item : to_ask) {
        sendRequest(item);
    }
}

void FindProcessor::receiveNodesVector(vector<NodeInfo>& nodes)
{
    for (auto item : nodes) {
        auto found = search_map.find(item.uuid);
        if (search_map.end() == found) {
            /* we have not encountered this node before */
            addNode(item);
        }
    }
    
    KBucketsTools::sortByDist(sorted_nodes, searched_guid, uuidGetter);
    //askNext(); // here just adding, ask in other place
}

void FindProcessor::onNodeResponse(uuid node_guid)
{
    auto found = search_map.find(node_guid);
    if (search_map.end() != found) {
        if (NodeSearchStruct::not_responding == found->second->state) {
            // if we previously have marked node as not_responding perhaps it was in k_best
            k_best.insert(found->second);
        }
        found->second->state = NodeSearchStruct::responded;
    }
}

bool FindProcessor::doesSearchFinished()
{
    if (true == k_best.doesSearchFinished()) {
        onSearchFinsihed();
        return true;
    }
    return false;
}

}
}
