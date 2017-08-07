#pragma once
#include "data_structures/messages/Message.h"
#include "data_structures/messages/MessageBuilder.pb.h"
#include "data_structures/NodeInfo.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>

namespace m2 {
namespace routing {

using std::vector;
class MessageBuilder
{
public:
    MessageBuilder();
    ~MessageBuilder();

    std::unique_ptr<Message> deserialize(vector<char> &buffer);
    vector<char> serialize(const PingRequestMessage &message);
    vector<char> serialize(const StoreRequestMessage &message);
    vector<char> serialize(const FindNodeRequestMessage &message);
    vector<char> serialize(const FindDataRequestMessage &message);
    vector<char> serialize(const PingResponseMessage &message);
    vector<char> serialize(const StoreResponsetMessage &message);
    vector<char> serialize(const FindNodeResponseMessage &message);
    vector<char> serialize(const FindDataResponseMessage &message);
};
}
}
