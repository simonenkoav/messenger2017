//
// Created by ovv on 09.08.17.
//

#include "servers/UdpServer.h"

using namespace m2::routing;

UdpServer::UdpServer(
    int port,
    io_service& io_service,
    std::function<void(vector<char>)> on_message_callback)
    : socket(io_service, udp::endpoint(udp::v4(), port))
    , on_message_callback(on_message_callback)
{}

void UdpServer::sendMessage(string ip, int port, vector<char> buff)
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

void UdpServer::startAccept()
{
    socket.async_receive_from(
        boost::asio::buffer(buffer),
        sender_endpoint,
        [this](const boost::system::error_code& e, size_t size){
            if (!e) {
                vector<char> received_buff(buffer.cbegin(), buffer.cend());
                //TODO сделать io_service.post(), чтобы не лочить прием udp пакетов
                this->on_message_callback(received_buff);
                // buffer.clear()
                this->startAccept();
                return;
            } else {
                //залогировать ошибку
            }
        });
}