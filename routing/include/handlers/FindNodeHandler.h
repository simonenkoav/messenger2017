#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindNodeHandler : protected CommandHandler
{

public:
    FindNodeHandler(Node& node);
    virtual ~FindNodeHandler();

    virtual void handleMessage(Message& message);

};

} // namespace m2
} // namespace routing
