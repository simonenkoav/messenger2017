#pragma once

#include "data_structures/Message.h"
#include "processors/Processor.h"
#include "handlers/CommandHandler.h"

#include <map>
#include <functional>
#include <memory>

namespace m2 {
namespace routing {

typedef Processor* PProcessor;
typedef std::function<PProcessor(Node&, boost::uuids::uuid)> ProcessorBuilder;

class RequestDispatcher: public CommandHandler
{
public:
    RequestDispatcher(Node& node, ProcessorBuilder process_builder);

    void process(const Message& message, OnRequestProcessed on_processed);
    void handleMessage(const Message& message);

private:
    void onProcessed(boost::uuids::uuid request_id, const Message& result);

    struct Request
    {
        std::unique_ptr<Processor> processor;
        OnRequestProcessed on_processed;
    };

    ProcessorBuilder pbuilder;
    std::map<boost::uuids::uuid, Request> requests;
};

} // namespace routing
} // namespace m2
