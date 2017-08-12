#pragma once
#include "data_structures/Message.h"
#include "data_structures/NodeContainingObject.h"
#include "utils/MessageBuilder.h"

namespace m2 {
namespace routing {
/// Command handler is an abstract class for all handlers of incoming messages
class CommandHandler : protected virtual NodeContainingObject
{
public:
    CommandHandler(Node& node);
    virtual ~CommandHandler();

public:
    virtual void handleMessage(const Message& message) = 0;

protected:
};

} // namespace routing
} // namespace m2
