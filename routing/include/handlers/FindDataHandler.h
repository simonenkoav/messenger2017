#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class FindDataHandler : protected CommandHandler
{


public:
    FindDataHandler(Node& node);
    ~FindDataHandler();

private:
};

} // namespace routing
} // namespace m2
