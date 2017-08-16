#pragma once
#include "processors/Processor.h"
#include "core/Node.h"

namespace m2 {
namespace routing {

class PingProcessor : public Processor
{
public:
    PingProcessor(Node& node, uuid request_id);
    virtual ~PingProcessor();

    // You have to put PingRequestMessage with node_info of the addressee.
    // It is a way to transmit node you want to ping.
    void process(const Message& message, const OnRequestProcessed& on_processed) override;

    void handleMessage(const Message& message) override;

protected:
    void onTimeoutExpired() override;
};
}
}
