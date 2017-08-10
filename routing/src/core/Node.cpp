#include <handlers/FindDataHandler.h>
#include <handlers/FindNodeHandler.h>
//#include "handlers/StoreHandler.h"
//#include "handlers/PingNodeHandler.h"

#include "core/Node.h"

class StoreHandler;
class PingNodeHandler;

class PingNodeProcessor;
class StoreProcessor;
class FindNodeProcessor;
class FindDataProcessor;

using namespace m2::routing;

Node::Node(string port)
    : io_service()
    , network_connector(std::stoi(port),
                        io_service,
                        [this](vector<char> data) {this->onMessageReceive(data);},
                        [](){})
    , dht()
{
    // create own uuid
    uuid my_guid = boost::uuids::basic_random_generator<boost::mt19937>()();

    // put int kbucket self_info
    self_info = {my_guid, network_connector.getMyIpAddress(), std::stoi(port)};
    kbuckets_manager.setNodeInfo(self_info);


// расскоментить, когда будут реализованы, пока не компилится
    handlers.insert({//{MessageType::PingRequest,     new PingNodeHandler(*this)},
                     //{MessageType::StoreRequest,    new StoreHandler(*this)},
                     {MessageType::FindNodeRequest, new FindNodeHandler(*this)},
                     {MessageType::FindDataRequest, new FindDataHandler(*this)},

                     //{MessageType::PingResponse,     new PingNodeProcessor(*this)},
                    // {MessageType::StoreResponse,    new StoreProcessor(*this)},
                    // {MessageType::FindNodeResponse, new FindNodeProcessor(*this)},
                    // {MessageType::FindDataResponse, new FindDataProcessor(*this)}});
                     {}});

  /*  processors.insert({{MessageType::PingResponse,     new PingNodeProcessor(*this)},
                       {MessageType::StoreResponse,    new StoreProcessor(*this)},
                       {MessageType::FindNodeResponse, new FindNodeProcessor(*this)},
                       {MessageType::FindDataResponse, new FindDataProcessor(*this)}});
*/
    // start accept incoming messages
    network_connector.startAccept();

    // send request to find k-neighbors
    processors[MessageType::FindNodeResponse]->process(self_info, nullptr);


};


void Node::start(uuid bootstrap_guid, string ip_address, string port)
{
    NodeInfo bootstrap_node = {bootstrap_guid, ip_address, std::stoi(port)};
    kbuckets_manager.insert(bootstrap_node);

    // find k-neighbors
    // ...

    // start accept incoming connections
    network_connector.startAccept();

    // start async work
    startAsyncUpdateKBuckets();
}

/*!
 * Find k-neighbors every T time;
 */
void Node::startAsyncUpdateKBuckets()
{
//    делаем async_wait и кладем что-то типо
//    processors[MessageType::FindNodeResponse].process(self_info.uuid);
}

/*!
 * handle incoming messages
 * @param buffer
 * @param size
 */
void Node::onMessageReceive(vector<char> buffer)
{
   // std::unique<Message> msg = ;
}

void Node::stop()
{
    network_connector.stop();
}

Node::~Node()
{
}

