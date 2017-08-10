#include "processors/StoreProcessor.h"


namespace m2 {
namespace routing {

StoreProcessor::StoreProcessor(Node & node, uuid request_id) : Processor(node, request_id)
{
}


StoreProcessor::~StoreProcessor()
{
}
}
}