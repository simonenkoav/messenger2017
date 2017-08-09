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
        int bucketIndex = KBucketsTools::distanceIndex(ourNodeInfo.uuid, newNodeInfo.uuid) - 1;

        if (bucketIndex != -1) //think about situation when bucketIndex == -1
        {
            if (interval_to_bucket.find(bucketIndex) != interval_to_bucket.end()) {
                //we have bucket with this bucketIndex

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
                        auto pairOfNewBuckets = KBucketsTools::split(bucket.known(), bucketIndex + 1); //index of bit
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
            } else {
                KBucket bucket;
                bucket.insert(newNodeInfo);
                interval_to_bucket.insert(std::pair<int, KBucket>(bucketIndex, bucket));
            }
        }
    }

    std::list<NodeInfo> KBucketsManager::getNeighbours(const boost::uuids::uuid &guid) const
    {
        if (interval_to_bucket.size() == 1) {
            return interval_to_bucket.at(0).known();
        }

        int bucketIndex = KBucketsTools::distanceIndex(ourNodeInfo.uuid, guid);

        std::list<NodeInfo> resultList;

        if (bucketIndex != -1) {
            auto bucket = interval_to_bucket.at(bucketIndex);
            auto closestNeighbours = bucket.known();
            resultList.insert(resultList.begin(), closestNeighbours.begin(), closestNeighbours.end());

            if (resultList.size() < Config::getK()) {
                auto additionalNodes = collectNodesFromNeighbouringBuckets(
                        Config::getK() - resultList.size(), bucketIndex, guid);
                resultList.insert(resultList.begin(), additionalNodes.begin(), additionalNodes.end());
            }
        }

        resultList = KBucketsTools::sortedByDist(resultList, guid);

        return resultList;
    }

    KBucketsManager::KBucketsManager()
    { //TODO remove it later, it's just for build

    }

    void KBucketsManager::setNodeInfo(const NodeInfo &nodeInfo) {
        ourNodeInfo = nodeInfo;
    }

    std::list<NodeInfo> KBucketsManager::collectNodesFromNeighbouringBuckets(
            const int count, const int bucketIndex, const boost::uuids::uuid &guid) const {
        std::list<NodeInfo> resultList;
        int previousIndex = bucketIndex - 1;
        int nextIndex = bucketIndex + 1;

        int previousDelta = previousIndex;
        int nextDelta = interval_to_bucket.size() - nextIndex;

        if (nextDelta > previousDelta) { //we should move in the forward direction
            while (nextIndex != interval_to_bucket.size()) {
                auto curNextBucketList = interval_to_bucket.at(nextIndex).known();
                resultList.insert(resultList.begin(), curNextBucketList.begin(), curNextBucketList.end());
                if (previousIndex != 0) {
                    auto curPrevBucketList = interval_to_bucket.at(previousIndex).known();
                    resultList.insert(resultList.begin(), curPrevBucketList.begin(), curPrevBucketList.end());
                    previousIndex--;
                }
                if (resultList.size() >= count) {
                    return sortByDistance(resultList, count, guid);
                }
                nextIndex++;
            }
        } else {
            while (previousIndex != 0) {
                auto curPrevBucketList = interval_to_bucket.at(previousIndex).known();
                resultList.insert(resultList.begin(), curPrevBucketList.begin(), curPrevBucketList.end());
                if (nextIndex != interval_to_bucket.size()) {
                    auto curNextBucketList = interval_to_bucket.at(nextIndex).known();
                    resultList.insert(resultList.begin(), curNextBucketList.begin(), curNextBucketList.end());
                    nextIndex++;
                }
                if (resultList.size() >= count) {
                    return sortByDistance(resultList, count, guid);
                }
                previousIndex--;
            }
        }

        return resultList;
    }

    std::list<NodeInfo> KBucketsManager::sortByDistance(const std::list<NodeInfo> &originalList,
                                    const int count, const boost::uuids::uuid &guid) const {
        auto resultList = KBucketsTools::sortedByDist(originalList, guid);
        auto end = std::next(resultList.begin(), std::min(resultList.size(), size_t(count)));
        auto cuttedList = std::list<NodeInfo>(resultList.begin(), end);
        resultList = std::move(cuttedList);
        return resultList;
    }

} // namespace routing
} // namespace m2

