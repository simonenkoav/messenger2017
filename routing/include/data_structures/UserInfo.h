#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <string>

namespace m2 {
namespace routing {

struct UserInfo
{
  boost::uuids::uuid uuid;
  std::string domain;

  UserInfo();
  ~UserInfo();
  UserInfo(boost::uuids::uuid uuid, std::string domain);

  inline bool isNil() {
      return uuid.is_nil();
  }
};

}
}
