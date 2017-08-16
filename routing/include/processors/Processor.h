#pragma once
#include "data_structures/NodeInfo.h"
#include "data_structures/Message.h"
#include "handlers/CommandHandler.h"

#include <boost/asio.hpp>
#include <boost/bind.hpp>
#include <boost/date_time/posix_time/posix_time.hpp>

namespace m2 {
namespace routing {
using boost::uuids::uuid;
class Processor : public virtual CommandHandler
{
public:
    Processor(Node& node, uuid request_id);
    virtual ~Processor();

    virtual bool isCompleted() = 0;
    Message* getResult();
    virtual void process(const Message& msg, OnRequestProcessed& on_processed) = 0;
    virtual void  handleMessage(const Message& message) = 0;

protected:
    Message* result;
    uuid request_id;
    bool completed;
    OnRequestProcessed callback;
    virtual void sendRequest(NodeInfo recipient) = 0;

    void setTimeout(boost::asio::io_service &io_service);
    //void setTimeout(boost::asio::io_service &io_service, std::function<void(Processor* proc_ptr)> function);
    virtual void onTimoutExpired() = 0;
};

} //namespace routing
} //namespace m2
