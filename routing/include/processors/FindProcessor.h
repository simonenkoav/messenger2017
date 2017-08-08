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

class FindProcessor : protected Processor
{
public:
    FindProcessor(Node& node, uuid target );
    ~FindProcessor();


public:
    void process(uuid guid);

protected:
    // Fields
    uuid searched_guid;
    map<uuid, processors::NodeSearchStruct*> search_map;
    processors::BestK k_best;
    list<processors::NodeSearchStruct> sorted_nodes;
    // TODO: use io_service from node (node_io). Only one event queue should be
    boost::asio::io_service io;

    // Methdods
    void sendRequest(processors::NodeSearchStruct* addressee);
    void timeoutExpires(uuid guid, boost::asio::deadline_timer* expired_timer);
    void clearSearchState();
    void selectNewForKBest();
    void askNext(int number = 0);

    virtual Message getMessage() = 0;

};
}
}
