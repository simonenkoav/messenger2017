#pragma once
#include "processors/Processor.h"

namespace m2{
namespace routing {
class StoreProcessor : protected Processor
{
public:
    StoreProcessor(Node& node, uuid request_id);
    virtual ~StoreProcessor();
};

}
}