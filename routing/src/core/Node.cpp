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
    : network_connector(std::stoi(port),
                       [this] (char* buffer, size_t size) {
                           this->onMessageReceive(buffer, size);
                       })
    , dht()
{
    // create own uuid
    uuid my_guid = boost::uuids::basic_random_generator<boost::mt19937>()();

    // put int kbucket self_info
    self_info = {my_guid, network_connector.getMyIpAddress(), std::stoi(port)};
    kbuckets_manager.setNodeInfo(self_info);

    handlers = {{MessageType::PingRequest,     PingNodeHandler(this)},
                {MessageType::StoreRequest,    StoreHandler(this)},
                {MessageType::FindNodeRequest, FindNodeHandler(this)},
                {MessageType::FindDataRequest, FindDataHandler(this)},

                {MessageType::PingResponse,     PingNodeProcessor(this)},
                {MessageType::StoreResponse,    StoreProcessor(this)},
                {MessageType::FindNodeResponse, FindNodeProcessor(this)},
                {MessageType::FindDataResponse, FindDataProcessor(this)}};

    processors = {{MessageType::PingResponse,     PingNodeProcessor(this)},
                  {MessageType::StoreResponse,    StoreProcessor(this)},
                  {MessageType::FindNodeResponse, FindNodeProcessor(this)},
                  {MessageType::FindDataResponse, FindDataProcessor(this)}};

    // start accept incoming messages
    network_connector.startAccept();

    // send request to find k-neighbors
    processors[MessageType::FindNodeResponse].process(self_info.uuid);

    startAsyncUpdateKBuckets();
};

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
void Node::onMessageReceive(char *buffer, size_t size)
{

}


Node::~Node()
{
}

