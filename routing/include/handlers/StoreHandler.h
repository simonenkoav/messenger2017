#pragma once
#include "handlers/CommandHandler.h"
namespace m2 {
namespace routing {
class StoreHandler : protected CommandHandler
{
public:
    StoreHandler(Node& node);
    virtual ~StoreHandler();

    virtual void handleMessage(Message& message);

};
}
}