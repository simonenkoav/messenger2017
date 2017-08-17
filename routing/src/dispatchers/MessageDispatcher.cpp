#include "dispatchers/MessageDispatcher.h"
#include "dispatchers/RequestDispatcher.h"

#include "processors/Processor.h"
#include "handlers/CommandHandler.h"

#include "processors/PingProcessor.h"
#include "processors/StoreProcessor.h"
#include "processors/FindNodeProcessor.h"
#include "processors/FindDataProcessor.h"

#include "handlers/PingHandler.h"
#include "handlers/StoreHandler.h"
#include "handlers/FindNodeHandler.h"
#include "handlers/FindDataHandler.h"

#include <exception>
#include <string>

namespace m2 {
namespace routing {


template<typename ProcessorType>
static ProcessorBuilder defaultProcessorBuilder()
{
    return [](Node& node, uuid request_id)->Processor* { return new ProcessorType(node, request_id); };
}

MessageDispatcher::MessageDispatcher(Node& node)
{
    // Create Handlers
    handlers[PingRequest] = new PingHandler(node);
    handlers[StoreRequest] = new StoreHandler(node);
    handlers[FindNodeRequest] = new FindNodeHandler(node);
    handlers[FindDataRequest] = new FindDataHandler(node);

    // Determine how FindProcessors are created
    auto ping_pbuilder = defaultProcessorBuilder<PingProcessor>();
    auto store_pbuilder = defaultProcessorBuilder<StoreProcessor>();
    auto find_node_pbuilder = defaultProcessorBuilder<FindNodeProcessor>();
    auto find_data_pbuilder = defaultProcessorBuilder<FindDataProcessor>();

    handlers[PingResponse] = request_dispatchers[PingRequest] = new RequestDispatcher(node, ping_pbuilder);
    handlers[StoreResponse] = request_dispatchers[StoreRequest] = new RequestDispatcher(node, store_pbuilder);
    handlers[FindNodeResponse] = request_dispatchers[FindNodeRequest] = new RequestDispatcher(node, find_node_pbuilder);
    handlers[FindDataResponse] = request_dispatchers[FindDataRequest] = new RequestDispatcher(node, find_data_pbuilder);
}

MessageDispatcher::~MessageDispatcher()
{
    for (auto it = handlers.begin(); it != handlers.end(); ++it) {
        delete it->second;
        it->second = nullptr;
    }
}

template<typename R>
static R& getByMessageType(const std::map<MessageType, R>& msg_type_map, MessageType type)
{
    auto it = msg_type_map.find(type);
    if (it != msg_type_map.end()) {
        throw std::runtime_error("Unexpected MessageType value " + std::to_string(type));
    }
    return it->second;
}

void MessageDispatcher::process(const Message& message, OnRequestProcessed on_processed)
{
    getByMessageType(request_dispatchers, message.message_type)->process(message, on_processed);
}

void MessageDispatcher::handleMessage(const Message& message)
{
    getByMessageType(request_dispatchers, message.message_type)->handleMessage(message);
}

} // namespace routing
} // namespace m2
