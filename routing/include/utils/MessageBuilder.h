#pragma once
#include "data_structures/Message.h"
#include "utils/MessageBuilderProto.pb.h"
#include "data_structures/NodeInfo.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <list>
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/string_generator.hpp>
#include <boost/lexical_cast.hpp>
#include <string>

namespace m2 {
namespace routing {

using std::vector;

class MessageBuilder
{
public:
    MessageBuilder();
    ~MessageBuilder();

    static std::unique_ptr<Message> deserialize(std::vector<char> &buffer);
    static std::vector<char> serialize(const PingRequestMessage &message);
    static std::vector<char> serialize(const StoreRequestMessage &message);
    static std::vector<char> serialize(const FindNodeRequestMessage &message);
    static std::vector<char> serialize(const FindDataRequestMessage &message);
    static std::vector<char> serialize(const PingResponseMessage &message);
    static std::vector<char> serialize(const StoreResponseMessage &message);
    static std::vector<char> serialize(const FindNodeResponseMessage &message);
    static std::vector<char> serialize(const FindDataResponseMessage &message);
};
}
}
