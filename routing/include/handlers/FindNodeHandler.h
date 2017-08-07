#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindNodeHandler : public CommandHandler
{

public:
    virtual Message* handleMessage(Message message);
    FindNodeHandler(Node& node);
    ~FindNodeHandler();


private:
    Node& node;
};

} // namespace m2
} // namespace routing
