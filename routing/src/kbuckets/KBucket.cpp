#include "kbuckets/KBucket.h"
#include "utils/Config.h"
#include <stdexcept>
#include <algorithm>

namespace m2 {
namespace routing {

KBucket::KBucket():
    k(Config::getK())
{}

KBucket::KBucket(const std::list<NodeInfo>& known_nodes):
    k(Config::getK()),
    nodes(known_nodes)
{}

bool KBucket::insert(const NodeInfo& node)
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->uuid == node.uuid) {
            throw std::runtime_error("KBucket::insert: duplicate uuid");
        }
    }

    if (filled < k) {
       nodes.push_front(node);
       ++filled;
       return true;
    }

    return false;
}

void KBucket::removeTail()
{
    if (!filled) {
        throw std::runtime_error("KBucket::removeTail: empty bucket");
    }
    
    nodes.pop_back();
}

void KBucket::moveToHead(const NodeInfo& node)
{
    auto found = std::find(nodes.begin(), nodes.end(), node);
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->uuid == node.uuid) {
            nodes.erase(found);
            nodes.push_front(node);
            return;
        }
    }
    
    throw std::runtime_error("KBucket::moveToHead: node not found");
}

bool KBucket::contains(const NodeInfo& node) const
{
    for (auto it = nodes.begin(); it != nodes.end(); ++it) {
        if (it->uuid == node.uuid) {
            return true;
        }
    }

    return false;
}

NodeInfo KBucket::tail() const
{
    if (!filled) {
        throw std::runtime_error("KBucket::tail: empty bucket");
    }

    return nodes.back();
}

} // namespace routing
} // namespace m2
