//
// Created by ovv on 05.08.17.
//
#pragma once

#include "boost/asio.hpp"
#include <vector>
#include <string>
#include <functional>


namespace m2 {
namespace routing {
using std::string;
using std::vector;

class NetworkConnector
{
 public:
  NetworkConnector(int port, std::function<void(char* buffer, size_t size)> onMessageReceiveCallback);

  NetworkConnector();

  void sendMessage(string ip, int port, vector<char> buffer);
  void startAccept();
  string getMyIpAddress();

 private:
  std::function<void(char* buffer, size_t size)> callback;
//    asio::socket
//    std::array<char, const_size> buffer;
};

} // end routing
} // end m2