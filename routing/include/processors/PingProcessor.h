#pragma once
#include "processors/Processor.h"

namespace m2 {
namespace routing {

class PingProcessor : protected Processor
{
public:
    PingProcessor(Node& node, uuid request_id);
    virtual ~PingProcessor();

    // You have to put PingRequestMessage with node_info of the addressee.
    // It is a way to transmit node you want to ping.
    virtual void process(Message& message);

    virtual void handleMessage(Message& message);

    void onTimeoutExpired();
};
}
}
