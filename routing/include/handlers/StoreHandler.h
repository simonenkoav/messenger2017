#pragma once
#include "handlers/CommandHandler.h"
#include "core/Node.h"

namespace m2 {
namespace routing {
class StoreHandler : public CommandHandler
{
public:
    StoreHandler(Node& node);
    virtual ~StoreHandler();

    virtual void handleMessage(const Message& message);

};
}
}