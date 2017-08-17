#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindNodeHandler : public CommandHandler
{

public:
    FindNodeHandler(Node& node);
    virtual ~FindNodeHandler();

    virtual void handleMessage(const Message& message);

};

} // namespace m2
} // namespace routing
