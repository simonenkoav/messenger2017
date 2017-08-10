//
// Created by ovv on 10.08.17.
//

#pragma once

#include "../../../../../../../../usr/include/c++/5/set"

#include "Connection/Connection.h"

namespace m2::routing {

class ConnectionManager
{
 public:
    ConnectionManager();

    ConnectionManager(const ConnectionManager&)            = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void startNewConnection(ConnectionPtr new_connection);
    void close(ConnectionPtr connection);
    void closeAll();

 private:
    std::set<ConnectionPtr> connections;
};

}
