#pragma once
#include "data_structures/Message.h"

namespace m2 {
namespace routing {

/// Command handler is an abstract class for all handlers of incoming messages
class CommandHandler
{
public:
    CommandHandler();
    ~CommandHandler();

public:
    virtual Message* handleMessage(Message message);

private:
};

} // namespace routing
} // namespace m2
