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

    std::list<NodeInfo> getNeighbours(const boost::uuids::uuid &guid) const; // @Wunder9l: need this api in FindProcessor

    void setNodeInfo(const NodeInfo &nodeInfo);

private:
    std::map<int, KBucket> interval_to_bucket;

    NodeInfo ourNodeInfo;

    int getIntervalInMap(int xorResult);

    void split(int interval, const NodeInfo &newNodeInfo);

};

} // namespace routing
} // namespace m2
