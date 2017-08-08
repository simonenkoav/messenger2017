#pragma once
#include <map>
#include <list>
#include <boost/uuid/uuid.hpp>

#include "data_structures/NodeSearchStruct.h"
#include "kbuckets/KBucketsTools.h"

namespace m2 {
namespace routing {
namespace processors {
using std::list;
using std::map;
using boost::uuids::uuid;

class BestK
{
public:
    BestK(int k, uuid target);
    ~BestK();

    void deleteItem(uuid item_uuid);
    NodeSearchStruct* getItem(uuid item_uuid);
    list<NodeSearchStruct*> getItemsToAsk(int number);
    void clear();
    size_t size();
    bool contains(uuid item_uuid);
    bool doesSearchFinished();

    // Insert item to k_best if it does not already exist there. If the list is full
    // it will check whether inserting item is better than other. If it is the item 
    // would be inserted
    // Return true if item was inserted, false otherwise
    bool insert(NodeSearchStruct* item);

private:
    // Do simply adding. No checks of k_limit. This method should be called if there less 
    // than k_limit elements
    void addItem(NodeSearchStruct* item);
    
    
    
    int k_limit;

    // The resource that we try to find the most closest to
    uuid target;

    // By this k_map you can easily access to NodeSearchStruct*
    map<uuid, NodeSearchStruct*> k_map;

    // List is sorted by distance to target (from the most close to the most remote)
    list<NodeSearchStruct*> sorted_list;

};

}
}
}