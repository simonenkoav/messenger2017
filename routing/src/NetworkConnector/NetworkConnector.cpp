//
// Created by ovv on 05.08.17.
//

#include "NetworkConnector/NetworkConnector.h"
#include <string>

using namespace m2::routing;

std::string NetworkConnector::getMyIpAddress()
{
    boost::asio::io_service io_service;

    boost::asio::ip::tcp::resolver resolver(io_service);
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *it;
    return endpoint.address().to_string();
}

void NetworkConnector::sendMessage(string ip, int port, vector<char> buffer)
{
    boost::asio::io_service io_service;
    boost::asio::ip::udp::endpoint endpoint(boost::asio::ip::address::from_string(ip), port);
    boost::asio::ip::udp::socket socket(io_service, boost::asio::ip::udp::endpoint(boost::asio::ip::udp::v4(), 0));
    socket.send_to(boost::asio::buffer(buffer, buffer.size()), endpoint);
    socket.close();
}

NetworkConnector::NetworkConnector() {}
