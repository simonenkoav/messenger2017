#include "processors/Processor.h"

namespace m2
{
namespace routing
{

Processor::Processor(Node& node, uuid request_id):NodeContainingObject(node), request_id(request_id)
{
}


Processor::~Processor()
{
}

}
}
