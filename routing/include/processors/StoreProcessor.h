#pragma once
#include "processors/Processor.h"
#include "core/Node.h"

namespace m2{
namespace routing {
class StoreProcessor : public Processor
{
public:
    StoreProcessor(Node& node, uuid request_id);
    virtual ~StoreProcessor();

    // You have to put StoreRequestMessage with node_info of the addressee.
    // It is a way to transmit node you want to store data at.
    virtual void process(const Message& message, const OnRequestProcessed& on_processed) override;

    virtual void handleMessage(const Message& message) override;

protected:

    virtual void onTimeoutExpired() override;

};

}
}
