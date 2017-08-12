#include "data_structures/BestK.h"

using namespace m2::routing::processors;

std::function<boost::uuids::uuid(const NodeSearchStruct* node)> uuidGetter =
[](const NodeSearchStruct* node) -> boost::uuids::uuid {
    return node->node_info.uuid;
};

BestK::BestK(int k) :k_limit(k)
{
}


BestK::~BestK()
{
    clear();
}

void m2::routing::processors::BestK::setTarget(uuid target)
{
    this->target = target;
}

void BestK::deleteItem(uuid item_uuid)
{
    auto it = k_map.find(item_uuid);
    if (k_map.end() != it) {
        sorted_list.remove(it->second);
        k_map.erase(it);
    }
}

NodeSearchStruct* BestK::getItem(uuid item_uuid)
{
    auto it = k_map.find(item_uuid);
    return (k_map.end() == it) ? nullptr : it->second;
}

list<NodeSearchStruct*> BestK::getItemsToAsk(int number)
{
    list<NodeSearchStruct*>result;
    if (0 < number) {
        for (auto item : sorted_list) {
            if (NodeSearchStruct::not_asked == item->state) {
                result.push_back(item);
                if (number <= result.size()) {
                    break;
                }
            }
        }
    }
    return result;
}

void BestK::clear()
{
    k_map.clear();
    sorted_list.clear();
}

size_t BestK::size()
{
    return sorted_list.size();
}

bool BestK::contains(uuid item_uuid)
{
    return k_map.end() != k_map.find(item_uuid);
}

bool m2::routing::processors::BestK::doesSearchFinished()
{
    if (k_limit == sorted_list.size()) {
        bool search_not_completed = false;
        for (auto item : sorted_list) {
            if (NodeSearchStruct::responded != item->state) {
                search_not_completed = true;
            }
        }
        return !search_not_completed;
    }
    return false;
}

bool m2::routing::processors::BestK::allPresentAreProcessed()
{
    bool not_all_processed = false;
    for (auto item : sorted_list) {
        if (NodeSearchStruct::responded != item->state) {
            not_all_processed = true;
            break;
        }
    }
    return !not_all_processed;
}

int m2::routing::processors::BestK::emptyPositions()
{
    int result = k_limit - size();
    return (0 <= result) ? result : 0;
}

list<NodeSearchStruct*> m2::routing::processors::BestK::getBest()
{
    return sorted_list;
}

bool BestK::insert(NodeSearchStruct * item)
{
    bool was_item_inserted = false;
    if (false == contains(item->node_info.uuid)) {
        if (size() < k_limit) {
            addItem(item);
            was_item_inserted = true;
        }
        else {
            NodeSearchStruct* worst_item = sorted_list.back();
            if (KBucketsTools::distance(worst_item->node_info.uuid, target) >
                KBucketsTools::distance(item->node_info.uuid, target)) {
                deleteItem(worst_item->node_info.uuid);
                addItem(item);
                was_item_inserted = true;
            }
        }
    }
    return was_item_inserted;
}

void m2::routing::processors::BestK::addItem(NodeSearchStruct * item)
{
    k_map[item->node_info.uuid] = item;
    sorted_list.push_back(item);
    KBucketsTools::sortByDist(sorted_list, target, uuidGetter);
}
