#include "kbuckets/KBucketsTools.h"
#include <cassert>
#include <vector>

namespace m2 {
namespace routing {

using boost::multiprecision::uint128_t;
using boost::uuids::uuid;
using processors::NodeSearchStruct;

uint128_t KBucketsTools::distance(const uuid& src, const uuid& dst)
{
    assert(uuidBitwidth() <= 128);

    uint128_t rv = 0; // ASSUMPTION: lowest bytes go first
    for (int i = 0; i < uuidWidth(); ++i) {
        rv = (rv << 8 * sizeof(uuid::value_type)) + src.data[i] ^ dst.data[i];
    }
    return rv;
}

template<typename T>
static int bsearchHighestBit(T val)
{
    int low = 0;
    int high = 8 * sizeof(T);

    while (high - low > 1) {
        int mid = low + (high - low) / 2;
        if (val < (1 << mid)) {
            high = mid;
        } else {
            low = mid;
        }
    }

    return val? high: 0;
}

int KBucketsTools::distanceIndex(const uuid& src, const uuid& dst)
{
    for (int i = uuidWidth() - 1; i >= 0; --i) {
        uuid::value_type val = src.data[i] ^ dst.data[i];
        if (val) {
            return i * 8 * sizeof(uuid::value_type) + bsearchHighestBit(val);
        }
    }

    return 0;
}

int KBucketsTools::commonPrefixBitsLen(const uuid& src, const uuid& dst)
{
    return uuidBitwidth() - distanceIndex(src, dst);
}

bool KBucketsTools::getBit(const uuid& src, int bit)
{
   assert(bit >= 0 && bit < 128);

   int value_bitwidth = 8 * sizeof(uuid::value_type);
   uuid::value_type mask = 1 << (bit % value_bitwidth);
   int offset = bit / value_bitwidth;

   return !!(src.data[offset] & mask);
}

std::list<NodeInfo> KBucketsTools::sortedByDist(const std::list<NodeInfo>& src, const uuid& dist_to)
{
    typedef std::pair<uint128_t, const NodeInfo*> DistData;
    std::vector<DistData> dists;
    for (auto it = src.begin(); it != src.end(); ++it) {
        dists.push_back(DistData(distance(it->uuid, dist_to), &*it));
    }
    std::sort(dists.begin(), dists.end(), [](const DistData& a, const DistData& b)->bool { return a > b; });

    std::list<NodeInfo> sorted;
    for (auto it = dists.begin(); it != dists.end(); ++it) {
        sorted.push_back(*it->second);
    }
    return sorted;
}

std::list<NodeSearchStruct>& KBucketsTools::sortedByDist(std::list<NodeSearchStruct>& src, const uuid& dist_to)
{
    typedef std::pair<uint128_t, const NodeInfo*> DistData;
    std::vector<DistData> dists;
    for (auto it = src.begin(); it != src.end(); ++it) {
        dists.push_back(DistData(distance(it->uuid, dist_to), &*it));
    }
    std::sort(dists.begin(), dists.end(), [](const DistData& a, const DistData& b)->bool { return a > b; });

    std::list<NodeSearchStruct> sorted;
    for (auto it = dists.begin(); it != dists.end(); ++it) {
        sorted.push_back(*it->second);
    }
    return sorted;
}

std::pair<std::list<NodeInfo>, std::list<NodeInfo>> KBucketsTools::split(const std::list<NodeInfo>& src, int by_bit)
{
    assert(by_bit >= 0 && by_bit < uuidBitwidth());

    std::list<NodeInfo> results[2];
    for (auto it = src.begin(); it != src.end(); ++it) {
        results[getBit(it->uuid, by_bit)].push_back(*it);
    }

    return std::pair<std::list<NodeInfo>,std::list<NodeInfo>>(results[0], results[1]);
}

NodeInfo KBucketsTools::closest(const NodeInfo& first, const NodeInfo& second, const uuid& origin)
{
    return distance(first.uuid, origin) > distance(second.uuid, origin)? second: first;
}

} // namespace routing
} // namespace m2
