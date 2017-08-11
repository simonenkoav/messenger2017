#include "dispatchers/RequestDispatcher.h"

#include <boost/uuid/uuid_io.hpp>
#include <iostream>
#include <exception>
#include <memory>

namespace m2 {
namespace routing {

using boost::uuids::uuid;
using boost::uuids::to_string;

RequestDispatcher::RequestDispatcher(Node& node, ProcessorBuilder pbuilder):
    NodeContainingObject(node),
    pbuilder(pbuilder)
{}

void RequestDispatcher::process(const Message& message, OnRequestProcessed on_processed)
{
    boost::uuids::uuid request_id = message.request_id;
    OnRequestProcessed on_processed_hook = std::bind(&RequestDispatcher::onProcessed, this, request_id, _1);
    Processor* processor = pbuilder(node, request_id);
    requests[request_id] = { std::unique_ptr<Processor>(processor), on_processed };
    processor->process(message, on_processed_hook);
}

void RequestDispatcher::handleMessage(const Message& message)
{
    auto it = requests.find(message.request_id);
    if (it == requests.end()) {
        std::cerr << "WRN[RequestDispatcher::handle] Unexpected request_id " << message.request_id << std::endl;
        return;
    }
    Request& request = it->second;
    request.processor->handleMessage(message);
}


void RequestDispatcher::onProcessed(boost::uuids::uuid request_id, const Message& result)
{
    auto it = requests.find(result.request_id);
    if (it == requests.end()) {
        throw std::runtime_error("RequestDispatcher::onProcessed received unexpected request_id "
                                 + to_string(request_id));
    }
    OnRequestProcessed on_processed = it->second.on_processed;
    requests.erase(it);
    on_processed(result);
}

} // namespace routing
} // namespace m2
