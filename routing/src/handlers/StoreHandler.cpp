#include "handlers/StoreHandler.h"


namespace m2 {
namespace routing {

StoreHandler::StoreHandler(Node& node): CommandHandler(node), NodeContainingObject(node)
{
}


StoreHandler::~StoreHandler()
{
}
}
}