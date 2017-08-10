#pragma once
#include "data_structures/Message.h"
#include "data_structures/MessageBuilder.pb.h"
#include "data_structures/NodeInfo.h"

#include <vector>
#include <string>
#include <memory>
#include <stdexcept>
#include <list>
#include <boost/uuid/uuid.hpp>

namespace m2 {
namespace routing {

using std::vector;

class MessageBuilder
{
public:
  MessageBuilder();
  ~MessageBuilder();

  std::unique_ptr<Message> deserialize(std::vector<char> &buffer);
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
