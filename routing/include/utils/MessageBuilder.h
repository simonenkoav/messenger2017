#pragma once
#include "data_structures/Message.h"
//#include "data_structures/messages/MessageBuilder.pb.h"
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
    static vector<char> serialize(const PingRequestMessage &message);
    static vector<char> serialize(const StoreRequestMessage &message);
    static vector<char> serialize(const FindNodeRequestMessage &message);
    static vector<char> serialize(const FindDataRequestMessage &message);
    static vector<char> serialize(const PingResponseMessage &message);
    static vector<char> serialize(const StoreResponseMessage &message);
    static vector<char> serialize(const FindNodeResponseMessage &message);
    static vector<char> serialize(const FindDataResponseMessage &message);
};
}
}
