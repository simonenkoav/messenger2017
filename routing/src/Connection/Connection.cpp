//
// Created by ovv on 10.08.17.
//

#include "Connection/Connection.h"

using namespace m2::routing;

Connection::Connection(tcp::socket&& socket)
    : socket(std::move(socket))
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
}

void Connection::doWrite()
{
}