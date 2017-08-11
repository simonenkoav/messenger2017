#pragma once
#include <boost/uuid/uuid.hpp>
#include <string>

namespace m2 {
namespace routing {

struct UserInfo
{
  boost::uuids::uuid uuid;
  std::string domain;

  UserInfo(boost::uuids::uuid uuid, std::string domain);
};

}
}
