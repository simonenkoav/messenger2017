//
// Created by ovv on 05.08.17.
//

#include "NetworkConnector/NetworkConnector.h"

using namespace m2::routing;

NetworkConnector::NetworkConnector(
    int port,
    io_service& io_service,
    std::function<void(vector<char>)> on_udp_callback,
    TcpCallback on_tcp_callback)
    : udp_server(port, io_service, on_udp_callback)
    , tcp_server(port, io_service, on_tcp_callback)
{}


void NetworkConnector::startAccept()
{
    udp_server.startAccept();
    tcp_server.startAccept();
}


std::string NetworkConnector::getMyIpAddress()
{
/*    boost::asio::ip::tcp::resolver resolver(socket.get_io_service());
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *it;
    return endpoint.address().to_string();*/
}

void NetworkConnector::stop()
{
    tcp_server.stop();
}

void NetworkConnector::sendMessage(string ip, int port, vector<char> buff)
{
    udp_server.sendMessage(ip, port, buff);
}