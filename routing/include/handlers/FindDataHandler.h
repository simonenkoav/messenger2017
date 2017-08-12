#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindDataHandler : public CommandHandler
{


public:
    FindDataHandler(Node& node);
    ~FindDataHandler();

    virtual void handleMessage(const Message& message);
};

} // namespace routing
} // namespace m2
