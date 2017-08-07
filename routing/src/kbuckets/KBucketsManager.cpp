#include <algorithm>
#include "kbuckets/KBucketsManager.h"

namespace m2 {
namespace routing {


    KBucketsManager::KBucketsManager(const NodeInfo &nodeInfo)
    : ourNodeInfo(nodeInfo)
    {
        KBucket initialKBucket;
        initialKBucket.insert(nodeInfo);
        interval_to_bucket.insert(std::pair<int, KBucket>(0, initialKBucket));
    }

    void KBucketsManager::insert(const NodeInfo &newNodeInfo) {
        int bucketIndex = KBucketsTools::distanceIndex(ourNodeInfo.uuid, newNodeInfo.uuid);

        if (bucketIndex != -1) //think about situation when bucketIndex == -1
        {
            auto bucket = interval_to_bucket[bucketIndex];

            bool bucketHasNewNode = bucket.contains(newNodeInfo);
            if (bucketHasNewNode) {
                bucket.moveToHead(newNodeInfo);
                return;
            }

            int K = Config::getK();
            if (bucket.knownCnt() < K) {
                bucket.insert(newNodeInfo);
            } else { //bucket is full
                bool bucketHasUs = bucket.contains(ourNodeInfo);
                if (bucketHasUs) { //this bucket contains ourNodeInfo
                    //check and ask Anton what he returns as first and what as second in pair
                    auto pairOfNewBuckets = KBucketsTools::split(bucket.known(), bucketIndex + 1);
                    interval_to_bucket.erase(bucketIndex);
                    interval_to_bucket.insert(std::pair<int, KBucket>(bucketIndex,
                                                                      KBucket(pairOfNewBuckets.first)));
                    interval_to_bucket.insert(std::pair<int, KBucket>(bucketIndex + 1,
                                                                      KBucket(pairOfNewBuckets.second)));
                    insert(newNodeInfo); //I hope I'm not mistaken
                } else {
                    auto lastConnectedNodeInfo = bucket.tail();
                    //TODO ping lastConnectedNodeInfo, do appropriate actions when it would answer on ping or not
                }

            }
        }
    }

    std::list<NodeInfo> KBucketsManager::getNeighbours(const boost::uuids::uuid &guid) const
    {
        return std::list<NodeInfo>();
    }

    KBucketsManager::KBucketsManager()
    { //TODO remove it later, it's just for build

    }

    void KBucketsManager::setNodeInfo(const NodeInfo &nodeInfo) {
        ourNodeInfo = nodeInfo;
    }

} // namespace routing
} // namespace m2

