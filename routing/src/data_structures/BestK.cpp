#include "data_structures/BestK.h"

using namespace m2::routing::processors;

BestK::BestK(int k, uuid target) :k_limit(k), target(target)
{
}


BestK::~BestK()
{
    clear();
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
            //TODO: call compare function
            if () {
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
    sorted_list.sort(TODO add sorting procedure);
}
