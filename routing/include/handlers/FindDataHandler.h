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

private:
    Node& node;
};

} // namespace routing
} // namespace m2
