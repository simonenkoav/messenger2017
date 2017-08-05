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
 
    bool insert(const m2::routing::NodeInfo& node); // new uuids only
    void replaceTail(const m2::routing::NodeInfo& node);
    void moveToHead(const m2::routing::NodeInfo& node); // erase NodeInfo with node.uuid & put new NodeInfo to head  

    std::list<m2::routing::NodeInfo> known() const { return nodes; }
    
    size_t knownCnt() const { return filled; }

    bool contains(const m2::routing::NodeInfo& node) const;
    NodeInfo tail() const;    

protected:
    std::list<m2::routing::NodeInfo> nodes;
    size_t filled; // NOTE: list::size O(capacity) implementation is allowed 
    size_t k;
};
    
} // namespace routing
} // namespace m2