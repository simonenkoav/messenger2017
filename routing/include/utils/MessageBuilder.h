#pragma once
#include "data_structures/messages/Message.h"
#include <vector>

namespace m2 {
namespace routing {

using std::vector;
class MessageBuilder
{
public:
    MessageBuilder();
    ~MessageBuilder();

    static Message deserialize(vector<char> buffer);
    static vector<char> serialize(Message message);
};
}
}
