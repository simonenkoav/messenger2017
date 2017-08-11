#pragma once
#include "processors/Processor.h"

namespace m2 {
namespace routing {

class PingProcessor : protected Processor
{
public:
    PingProcessor(Node& node, uuid request_id);
    virtual ~PingProcessor();
};
}
}
