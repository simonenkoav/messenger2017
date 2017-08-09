#pragma once
#include "handlers/CommandHandler.h"
namespace m2 {
namespace routing {
class PingHandler : protected CommandHandler
{
public:
    PingHandler(Node& node);
    virtual ~PingHandler();

    virtual void handleMessage(Message& message);
};
}
}
