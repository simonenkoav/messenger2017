#include "processors/PingProcessor.h"


namespace m2 {
namespace routing {

PingProcessor::PingProcessor(Node & node, uuid request_id) : Processor(node, request_id)
{
}


PingProcessor::~PingProcessor()
{
}
}
}