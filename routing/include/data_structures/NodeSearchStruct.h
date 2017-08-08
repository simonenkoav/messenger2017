#pragma once
#include "data_structures/NodeInfo.h"

namespace m2 {
namespace routing {
namespace processors {
struct NodeSearchStruct {
    enum state_type { not_asked, wait_for_responce, responded, not_responding } state;
    NodeInfo node_info;
    //std::mutex state_change_mutex;

    NodeSearchStruct(NodeInfo node) :node_info(node), state(state_type::not_asked) {}
};
}
}
}
