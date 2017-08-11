//
// Created by ovv on 10.08.17.
//

#include "Connection/Connection.h"

using namespace m2::routing;

Connection::Connection(tcp::socket&& socket, TcpCallback callback)
    : socket(std::move(socket))
    , on_request_receive(callback)
{}

void Connection::start()
{
    doRead();
}

void Connection::close()
{
    socket.close();
}

void Connection::doRead()
{
//TODO асинхр.чтение с сокета до конца http заголовков
}

void Connection::doWrite()
{
//TODO асинхр.запись
}