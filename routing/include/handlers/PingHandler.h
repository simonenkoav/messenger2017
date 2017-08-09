#pragma once
#include "handlers/CommandHandler.h"
namespace m2 {
namespace routing {
class PingHandler : protected CommandHandler
{
public:
    virtual void handleMessage(Message& message);
    PingHandler(Node& node);
    virtual ~PingHandler();
};
}
}
