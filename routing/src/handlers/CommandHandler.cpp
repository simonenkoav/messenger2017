#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

CommandHandler::CommandHandler()
{
}

CommandHandler::~CommandHandler()
{
}

Message *CommandHandler::handleMessage(Message message) {
    return nullptr;
}

} // namespace routing
} // namespace m2
