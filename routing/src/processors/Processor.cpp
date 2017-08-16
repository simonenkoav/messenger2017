#include "processors/Processor.h"


namespace m2 {
namespace routing {

Processor::Processor(Node& node, uuid request_id) :CommandHandler(node), request_id(request_id)
{
    completed = false;
}

void Processor::setTimeout(boost::asio::io_service &io_service )
{
    auto timer = new boost::asio::deadline_timer(io_service, Config::getResponseTimeout());
    timer->async_wait(boost::bind(&Processor::onTimoutExpired, this));
}


Processor::~Processor()
{
}

}
}
