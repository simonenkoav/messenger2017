#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {
class PingHandler : public CommandHandler
{
public:
    PingHandler(Node& node);
    virtual ~PingHandler();

    virtual void handleMessage(const Message& message);
};
}
}
