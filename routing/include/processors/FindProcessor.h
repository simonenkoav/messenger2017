#pragma once
#include <boost/uuid/uuid.hpp>
#include <list>
#include <vector>
#include <map>
#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

#include "handlers/CommandHandler.h"
#include "data_structures/NodeInfo.h"
#include "data_structures/NodeSearchStruct.h"
#include "data_structures/BestK.h"
#include "Processor.h"
#include "utils/Config.h"
#include "core/Node.h"
#include "utils/MessageBuilder.h"


namespace m2 {
namespace routing {

using boost::uuids::uuid;
using std::vector;
using std::list;
using std::map;

class FindProcessor : public Processor
{
public:
    FindProcessor(Node& node, uuid request_id );
    ~FindProcessor();


public:
    virtual void process(Message& message, OnRequestProcessed on_processed);
    virtual bool isCompleted() = 0;

protected:
    // Fields
    uuid searched_guid;
    map<uuid, processors::NodeSearchStruct*> search_map;
    processors::BestK k_best;
    list<processors::NodeSearchStruct> sorted_nodes;

    // Methdods
    void sendRequest(processors::NodeSearchStruct* addressee);
    void onTimeoutExpired(uuid guid, boost::asio::deadline_timer* expired_timer);
    void clearSearchState();
    size_t selectNewForKBest();
    void addNode(NodeInfo node_info);
    size_t askNext(int number = 0);
    void receiveNodesList(list<NodeInfo>& nodes);
    void onNodeResponse(uuid node_guid);
    bool doesSearchFinished();

    virtual vector<char> getMessage() = 0;
    virtual void onSearchFinsihed() = 0;
    virtual uuid getGuid(Message& message) = 0;
};
}
}
