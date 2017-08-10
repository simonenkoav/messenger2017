//
// Created by ovv on 09.08.17.
//

#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ip/udp.hpp"
#include <vector>

using boost::asio::io_service;
using std::vector;
using std::string;
using namespace boost::asio::ip;


namespace m2::routing {

class UdpServer
{
 public:
    UdpServer(int port,
              io_service& service,
              std::function<void(vector<char>)> on_message_callback);
    UdpServer()           = delete;
    UdpServer(UdpServer&) = delete;

    void sendMessage(string ip, int port, vector<char> buffer);
    void startAccept();

 private:
    udp::endpoint sender_endpoint;
    std::function<void(vector<char>)> on_message_callback;
    udp::socket socket;
    std::array<char, 2000> buffer;

};

}
