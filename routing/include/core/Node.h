#pragma once
#include <string>
#include <unordered_map>

#include "boost/uuid/uuid.hpp"
#include "boost/uuid/uuid_generators.hpp"

#include "handlers/CommandHandler.h"
#include "processors/Processor.h"

#include "processors/Processor.h"
#include "handlers/CommandHandler.h"


#include "data_structures/Message.h"
#include "kbuckets/KBucketsManager.h"
#include "NetworkConnector/NetworkConnector.h"
#include "DHT/DHT.h"

using std::string;
using boost::uuids::uuid;

namespace m2 {
namespace routing {


class Node
{
public:
    Node(string port);
    ~Node();


    void start(uuid bootstrap_guid, string ip_address, string port);
        // void stop();
private:
    void onMessageReceive(char* buffer, size_t size);

    DHT dht;
    NodeInfo self_info;
    NetworkConnector network_connector;
    KBucketsManager kbuckets_manager;
    std::unordered_map<MessageType, CommandHandler *, MessageTypeHash> handlers;
    std::unordered_map<MessageType, Processor *, MessageTypeHash> processors;

    friend class PingProcessor;
    friend class StoreProcessor;
    friend class FindProcessor;
    friend class FindNodeProcessor;
    friend class FindDataProcessor;

    friend class PingHandler;
    friend class StoreHandler;
    friend class FindNodeHandler;
    friend class FindDataHandler;
};

} // namespace routing
} // namespace m2
