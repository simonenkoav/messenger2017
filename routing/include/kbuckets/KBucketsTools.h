#pragma once
//#include "kbuckets/KBucketsTools.h"
#include "data_structures/NodeSearchStruct.h"
#include <boost/multiprecision/cpp_int.hpp>
#include <boost/uuid/uuid.hpp>
#include <list>

namespace m2 {
namespace routing {
using m2::routing::processors::NodeSearchStruct;

class KBucketsTools
{
    // Treat uuid as little-endian uint128  

public:
    KBucketsTools() = delete;

    static int uuidWidth() { return boost::uuids::uuid::static_size(); } 
    static int uuidBitwidth() { return boost::uuids::uuid::static_size() * 8; }
    
    static boost::multiprecision::uint128_t distance(const boost::uuids::uuid& src, const boost::uuids::uuid& dst);
    static int distanceIndex(const boost::uuids::uuid& src, const boost::uuids::uuid& dst); // uuidBitwidth - commonPrefixBitsLen
    static int commonPrefixBitsLen(const boost::uuids::uuid& src, const boost::uuids::uuid& dst); 
    static bool getBit(const boost::uuids::uuid& src, int bit);

    static std::list<NodeInfo> sortedByDist(const std::list<NodeInfo>& src, const boost::uuids::uuid& dist_to);
    static std::list<NodeSearchStruct>& KBucketsTools::sortedByDist(std::list<NodeSearchStruct>& src, const uuid& dist_to);
    static std::pair<std::list<NodeInfo>, std::list<NodeInfo>> split(const std::list<NodeInfo>& src, int by_bit);
    static NodeInfo closest(const NodeInfo& x, const NodeInfo& y, const boost::uuids::uuid& origin); // ret x unless y is closer
};

} // namespace routing
} // namespace m2
