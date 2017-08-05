#pragma once
#include <string>
#include "boost/uuid/uuid.hpp"
//#include "CommandHandler.h"
#include "data_structures/Message.h"
#include "kbuckets/KBucketsManager.h"
#include "NetworkConnector/NetworkConnector.h"
#include "DHT/DHT.h"

using std::string;
using boost::uuids::uuid;

namespace m2 {
namespace routing {


class Node //friend class CommandHandler
{
public:
    Node(string port) {};
    ~Node();



    void start(uuid bootstrap_guid, string ip_address, string port);
        // void stop();
private:
    void onMessageReceive(char* buffer, size_t size);

    DHT dht;
    NetworkConnector networkConnector;
    KBucketsManager kbucketsManager;

};

} // namespace routing
} // namespace m2
