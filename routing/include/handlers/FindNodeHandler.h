#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindNodeHandler : CommandHandler
{

public:
    virtual void handleMessage(Message message);
    FindNodeHandler(Node& node);
    ~FindNodeHandler();


private:
};

} // namespace m2
} // namespace routing
