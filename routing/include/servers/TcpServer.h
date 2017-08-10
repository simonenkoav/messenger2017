//
// Created by ovv on 09.08.17.
//

#pragma once

#include "ConnectionManager/ConnectionManager.h"

#include "boost/asio.hpp"
#include "boost/asio/ip/tcp.hpp"
#include <vector>

using boost::asio::io_service;
using std::vector;
using std::string;
using namespace boost::asio::ip;

namespace m2 {
namespace routing {

class TcpServer
{
 public:
    TcpServer(int port, io_service& service);

    void startAccept();
    void stop();

 private:
    ConnectionManager connection_manager;
    tcp::socket socket;
    tcp::acceptor acceptor;
};

} // end routing
} // end m2