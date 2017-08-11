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

void Processor::setTimeout(boost::asio::io_service &io_service, std::function<void(Processor* proc_ptr)> function)
{
    auto timer = new boost::asio::deadline_timer(io_service, Config::getResponseTimeout());
    timer->async_wait(boost::bind(function, this));
}


Processor::~Processor()
{
}

}
}
