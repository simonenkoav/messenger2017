#include "processors/Processor.h"

namespace m2 {
namespace routing {

Processor::Processor(Node& node, uuid request_id) :CommandHandler(node), request_id(request_id)
{
    completed = false;
}

Message * Processor::getResult()
{
    return result;
}


Processor::~Processor()
{
}

}
}
