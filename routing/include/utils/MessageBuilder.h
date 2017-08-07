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

    static Message deserialize(vector<char> buffer);
    static vector<char> serialize(const PingRequestMessage &message);
};
}
}
