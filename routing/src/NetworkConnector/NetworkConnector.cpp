//
// Created by ovv on 05.08.17.
//

#include "NetworkConnector/NetworkConnector.h"
#include <string>

using namespace m2::routing;

NetworkConnector::NetworkConnector(
    int port,
    io_service& io_service,
    std::function<void(vector<char>)> on_message_callback)
    : socket(io_service, udp::endpoint(udp::v4(), port))
    , on_message_callback(on_message_callback)
{}


void NetworkConnector::startAccept()
{
    udp::endpoint sender_endpoint;
    socket.async_receive_from(
        boost::asio::buffer(buffer),
        sender_endpoint,
        [this](const boost::system::error_code& e, size_t size){
            if (!e) {
                vector<char> received_buff(buffer.cbegin(), buffer.cend());
                this->on_message_callback(received_buff);
                this->startAccept();
                return;
            } else {
                //залогировать ошибку
            }
        });
}


std::string NetworkConnector::getMyIpAddress()
{

    boost::asio::ip::tcp::resolver resolver(socket.get_io_service());
    boost::asio::ip::tcp::resolver::query query(boost::asio::ip::host_name(), "");
    boost::asio::ip::tcp::resolver::iterator it = resolver.resolve(query);
    boost::asio::ip::tcp::endpoint endpoint = *it;
    return endpoint.address().to_string();
}

void NetworkConnector::sendMessage(string ip, int port, vector<char> buff)
{
    udp::endpoint target(address::from_string(ip), port);
    socket.async_send_to(
        boost::asio::buffer(buff),
        target,
        [](const boost::system::error_code& e, size_t bytes_transered) {
            if (e) {
            //заллогировать
            } else {
            }
        });
}
