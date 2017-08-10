//
// Created by ovv on 10.08.17.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ip/tcp.hpp"
#include "../../../../../../../../usr/include/c++/5/memory"

using namespace boost::ip;

namespace m2::routing {

class Connection : public std::enable_shared_from_this<Connection>
{
 public:
    Connection(tcp::socket&& socket);
    Connection(Connection&) = delete;
    Connection& operator= (const Connection&) = delete;

    void start();
    void close();

 private:
    doRead();
    doWrite();

    tcp::socket socket;
    std::array<char, 2000> buffer;
};

typedef std::shared_ptr<Connection> ConnectionPtr

}
