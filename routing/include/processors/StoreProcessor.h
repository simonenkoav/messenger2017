#pragma once
#include "processors/Processor.h"

namespace m2{
namespace routing {
class StoreProcessor : public Processor
{
public:
    StoreProcessor(Node& node, uuid request_id);
    virtual ~StoreProcessor();

    // You have to put StoreRequestMessage with node_info of the addressee.
    // It is a way to transmit node you want to store data at.
    virtual void process(Message& message, OnRequestProcessed on_processed);

    virtual void handleMessage(Message& message);

protected:

    virtual void onTimeoutExpired();

};

}
}
