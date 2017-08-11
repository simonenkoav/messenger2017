#pragma once

#include "dispatchers/RequestDispatcher.h"

#include <functional>

namespace m2 {
namespace routing {

class MessageDispatcher
{
public:
    MessageDispatcher(Node& node); // tweak handlers/processors creatation here
    ~MessageDispatcher();

    void process(const Message& message, OnRequestProcessed on_processed);
    void handleMessage(const Message& message);

private:
    std::map<MessageType, RequestDispatcher*> request_dispatchers;
    std::map<MessageType, CommandHandler*> handlers;
};

} // namespace routing
} // namespace m2
