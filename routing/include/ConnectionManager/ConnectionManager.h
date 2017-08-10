//
// Created by ovv on 10.08.17.
//

#pragma once

#include <set>
#include "Connection/Connection.h"

namespace m2 {
namespace routing {

class ConnectionManager
{
 public:
    ConnectionManager() = default;

    ConnectionManager(const ConnectionManager&)            = delete;
    ConnectionManager& operator=(const ConnectionManager&) = delete;

    void startNewConnection(ConnectionPtr new_connection);
    void close(ConnectionPtr connection);
    void closeAll();

 private:
    std::set<ConnectionPtr> connections;
};

}
}
