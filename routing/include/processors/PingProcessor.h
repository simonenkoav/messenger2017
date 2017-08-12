#pragma once
#include "processors/Processor.h"

namespace m2 {
namespace routing {

class PingProcessor : public Processor
{
public:
    PingProcessor(Node& node, uuid request_id);
    virtual ~PingProcessor();

    // You have to put PingRequestMessage with node_info of the addressee.
    // It is a way to transmit node you want to ping.
    virtual void process(Message& message, OnRequestProcessed on_processed);

    virtual void handleMessage(const Message& message);

protected:
    virtual void onTimeoutExpired();
};
}
}
