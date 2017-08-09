#pragma once

#include "data_structures/NodeInfo.h"

#include <boost/multiprecision/cpp_int.hpp>
#include <boost/uuid/uuid.hpp>
#include <list>
#include <functional>

namespace m2 {
namespace routing {

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

    template<typename T>
    static void sortByDist(std::list<T>& lst, const boost::uuids::uuid& origin, std::function<boost::uuids::uuid(const T&)> uuid_getter)
    {
        auto key = [uuid_getter, origin] (const T& a) -> boost::multiprecision::uint128_t { return distance(uuid_getter(a), origin); };
        auto compar = [key] (const T& a, const T& b) -> bool { return key(a) < key(b); };
        lst.sort(compar);
    }

    static std::pair<std::list<NodeInfo>, std::list<NodeInfo>> split(const std::list<NodeInfo>& src, int by_bit);
    static NodeInfo closest(const NodeInfo& x, const NodeInfo& y, const boost::uuids::uuid& origin); // ret x unless y is closer
};

} // namespace routing
} // namespace m2
