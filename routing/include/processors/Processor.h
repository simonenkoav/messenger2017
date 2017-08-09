#pragma once
#include "data_structures/NodeInfo.h"
#include "data_structures/Message.h"
#include "handlers/CommandHandler.h"

namespace m2 {
namespace routing {
class Processor : protected virtual CommandHandler
{
public:
    Processor(Node& node, uuid request_id);
    virtual ~Processor() {}

    virtual bool isCompleted() = 0;
    Message* getResult();
    virtual void process(NodeInfo node_info, void* additional_data) = 0;
    virtual void  handleMessage(Message& message) = 0;

protected:
    Message* result;
    uuid request_id;
    bool completed;
    virtual void sendRequest(NodeInfo recipient) = 0;
};

} //namespace routing
} //namespace m2
