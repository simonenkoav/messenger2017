#include <handlers/FindDataHandler.h>
#include <handlers/FindNodeHandler.h>
#include "processors/FindDataProcessor.h"
#include "processors/FindNodeProcessor.h"
#include "core/Node.h"

using namespace m2::routing;

Node::Node(string port)
    : network_connector(std::stoi(port),
                       [this] (char* buffer, size_t size) {
                           this->onMessageReceive(buffer, size);
                       })
    , dht()
{
    // create own uuid
    uuid my_guid = boost::uuids::basic_random_generator()();

    // put int kbucket self_info
    self_info = {my_guid, network_connector.getMyIpAddress(), std::stoi(port)};
    kbuckets_manager.setNodeInfo(self_info);

    handlers = {std::make_pair(MessageType::PingRequest,     PingNodeHandler(this)),
                std::make_pair(MessageType::StoreRequest,    StoreHandler(this)),
                std::make_pair(MessageType::FindNodeRequest, FindNodeHandler(this)),
                std::make_pair(MessageType::FindDataRequest, FindDataHandler(this)),

                std::make_pair(MessageType::PingResponse,     PingNodeProcessor(this)),
                std::make_pair(MessageType::StoreResponse,    StoreProcessor(this)),
                std::make_pair(MessageType::FindNodeResponse, FindNodeProcessor(this)),
                std::make_pair(MessageType::FindDataResponse, FindDataProcessor(this))};
    // TODO: ERROR! pay attention that both handlers and processors have to contain the same copy of ProcessorClass
    processors = {std::make_pair(MessageType::PingResponse,     PingNodeProcessor(this)),
                  std::make_pair(MessageType::StoreResponse,    StoreProcessor(this)),
                  std::make_pair(MessageType::FindNodeResponse, FindNodeProcessor(this)),
                  std::make_pair(MessageType::FindDataResponse, FindDataProcessor(this))};

    // start accept incoming messages
    network_connector.startAccept();

    // send request to find k-neighbors
    processors[MessageType::FindNodeResponse].process(self_info, NULL);

};

Node::~Node()
{
}

} // namespace routing
} // namespace m2
