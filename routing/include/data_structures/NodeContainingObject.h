#pragma once
#include "core/Node.h"

namespace m2 {
namespace routing {
class NodeContainingObject
{
public:

    NodeContainingObject(Node& node):node(node)
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
