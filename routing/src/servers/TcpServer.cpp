//
// Created by ovv on 09.08.17.
//

#include "servers/TcpServer.h"

using namespace m2::routing;

TcpServer::TcpServer(int port, io_service &service, std::function<void()> callback)
    : acceptor(service)
    , socket(service)
    , callback(callback)
{
    acceptor.open(tcp::v4());
    acceptor.bind(tcp::endpoint(tcp::v4(), port));
    acceptor.set_option(boost::asio::ip::tcp::acceptor::reuse_address(true));
    acceptor.listen();
}

void TcpServer::startAccept()
{
    acceptor.async_accept(socket, [this](boost::system::error_code& ec){
        if(!acceptor.is_open()) {
            return;
        }

        if(!ec) {
            connection_manager.startNewConnection(
                std::make_shared<Connection>(std::move(socket), callback));
        }
        startAccept();
    });
}

void TcpServer::stop()
{
    acceptor.close();
    connection_manager.closeAll();
}