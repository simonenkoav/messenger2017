#pragma once
#include <boost/uuid/uuid.hpp>
#include <list>
#include <vector>

#include "handlers/CommandHandler.h"
#include "data_structures/NodeInfo.h"
#include "Processor.h"
#include "utils/Config.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

using boost::uuids::uuid;
using std::vector;
using std::list;

class FindProcessor : Processor
{

public:
    FindProcessor(Node& node);
    ~FindProcessor();


public:

    virtual Message* handleMessage(Message message);
    void process(uuid guid);

protected:
    // Fields
    Node& node;
    uuid searched_guid;
    list<NodeInfo> not_asked;
    list<NodeInfo> wait_for_answer;
    list<NodeInfo> k_best;

    // Methdods
    virtual void sendRequest(NodeInfo recipient) = 0;
};
}
}
