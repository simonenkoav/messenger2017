//
// Created by ovv on 10.08.17.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ip/tcp.hpp"
#include <memory>
#include <vector>

using namespace boost::asio::ip;
using std::vector;

namespace m2 {
namespace routing {

typedef std::function<void(vector<char>)> TcpCallback;

class Connection : public std::enable_shared_from_this<Connection> {
 public:
    Connection(tcp::socket&& socket, TcpCallback callback);
    Connection(Connection &) = delete;
    Connection &operator=(const Connection &) = delete;

    void start();
    void close();

 private:
    void doRead();
    void doWrite();

    TcpCallback on_request_receive;
    tcp::socket socket;
    std::array<char, 2000> buffer;
};

typedef std::shared_ptr<Connection> ConnectionPtr;

}
}
