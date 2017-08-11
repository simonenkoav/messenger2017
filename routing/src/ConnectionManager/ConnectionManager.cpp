//
// Created by ovv on 10.08.17.
//

#include "ConnectionManager/ConnectionManager.h"

using namespace m2::routing;

void ConnectionManager::startNewConnection(ConnectionPtr new_connection)
{
    connections.insert(new_connection);
    new_connection->start();
}

void ConnectionManager::close(ConnectionPtr connection)
{
    connection -> close();
    connections.erase(connection);
}

void ConnectionManager::closeAll()
{
    for (auto& connection: connections) {
        connection->close();
    }
    connections.clear();
}