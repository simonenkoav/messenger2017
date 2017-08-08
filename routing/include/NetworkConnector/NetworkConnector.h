//
// Created by ovv on 05.08.17.
//
#pragma once

#include "boost/asio.hpp"
#include "boost/asio/ip/udp.hpp"

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

class NetworkConnector final
{
 public:
  NetworkConnector(int port,
                   io_service& service,
                   std::function<void(vector<char>)> on_message_callback);


  NetworkConnector() = default;
  NetworkConnector(NetworkConnector&) = delete;

  void sendMessage(string ip, int port, vector<char> buffer);
  void startAccept();
  string getMyIpAddress();

 private:
  std::function<void(vector<char> buffer)> on_message_callback;
  udp::socket socket;
  std::array<char, 2000> buffer;
};

} // end routing
} // end m2