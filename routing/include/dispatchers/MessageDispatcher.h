#pragma once

#include "data_structures/Message.h"

namespace m2 {
namespace routing {
class RequestDispatcher;
class CommandHandler;
class Node;
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
