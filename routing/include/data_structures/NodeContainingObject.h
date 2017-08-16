#pragma once

namespace m2 {
namespace routing {
class Node;
class NodeContainingObject
{
public:

    NodeContainingObject(Node& node) : node(node)
    {
    }

    ~NodeContainingObject()
    {
    }

protected:
    Node& node;
};
}

}
