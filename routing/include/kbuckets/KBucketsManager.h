#pragma once

#include <map>
#include <list>
#include <algorithm>
#include <boost/uuid/uuid.hpp>

#include "data_structures/NodeInfo.h"
#include "kbuckets/KBucket.h"
#include "kbuckets/KBucketsTools.h"
#include "utils/Config.h"

namespace m2 {
namespace routing {

class KBucketsManager
{
public:
    KBucketsManager(); //TODO remove it, it's temporary for build
    KBucketsManager(const NodeInfo &nodeInfo);

    void insert(const NodeInfo &nodeInfo);

    std::list<NodeInfo> getNeighbours(const boost::uuids::uuid &guid) const;

    void setNodeInfo(const NodeInfo &nodeInfo);

private:
    std::map<int, KBucket> interval_to_bucket;

    NodeInfo ourNodeInfo;

    int getIntervalInMap(int xorResult);

    void split(int interval, const NodeInfo &newNodeInfo);

    std::list<NodeInfo> collectNodesFromNeighbouringBuckets(int count, int bucketIndex,
                                                            const boost::uuids::uuid &guid) const;

    std::list<NodeInfo> sortByDistance(const std::list<NodeInfo> &originalList, const int count,
                                       const boost::uuids::uuid &guid) const;



};
        
} // namespace routing
} // namespace m2