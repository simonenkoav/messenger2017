//
// Created by ovv on 05.08.17.
//
#pragma once

<<<<<<< HEAD

#include "boost/asio/ip/tcp.hpp"
#include "servers/UdpServer.h"
#include "servers/TcpServer.h"
=======
#include "boost/asio.hpp"
#include "boost/asio/ip/udp.hpp"
>>>>>>> bf7731b151cc2f47aef9feab4b6df15ce9105b7f

#include <vector>
#include <string>
#include <functional>


namespace m2 {
namespace routing {

class Node;

using std::string;
using std::vector;
using namespace boost::asio::ip;
using boost::asio::io_service;

typedef std::function<void()> TcpCallback;

class NetworkConnector final
{
 public:
    NetworkConnector(int port,
                     io_service& service,
                     std::function<void(vector<char>)> on_message_callback,
                     TcpCallback on_tcp_callback);
                     std::function<void(vector<char>)> on_message_callback);

    NetworkConnector() = default;
    NetworkConnector(NetworkConnector&) = delete;

    void sendMessage(string ip, int port, vector<char> buffer);
    void startAccept();
    void stop();
    string getMyIpAddress();

 private:
    UdpServer udp_server;
    TcpServer tcp_server;
};

} // end routing
} // end m2