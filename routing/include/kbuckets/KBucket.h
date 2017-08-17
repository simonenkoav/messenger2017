#pragma once
#include "data_structures/NodeInfo.h"
#include <list>

namespace m2 {
namespace routing {

class KBucket final
{
public:
    KBucket();
    KBucket(const std::list<NodeInfo>& known_nodes); // WRN: doesn't check for uuid duplicates
 
    bool insert(const NodeInfo& node); // new uuids only
    void removeTail();
    void moveToHead(const NodeInfo& node); // erase NodeInfo with node.guid & put new NodeInfo to head  

    std::list<NodeInfo> known() const { return nodes; }
    
    size_t knownCnt() const { return filled; }

    bool contains(const NodeInfo& node) const;
    NodeInfo tail() const;    

protected:
    std::list<NodeInfo> nodes;
    size_t filled; // NOTE: list::size O(capacity) implementation is allowed 
    size_t k;
};
    
} // namespace routing
} // namespace m2