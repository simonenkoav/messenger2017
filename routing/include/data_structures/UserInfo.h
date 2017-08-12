#pragma once
#include <boost/uuid/uuid.hpp>
#include <boost/uuid/nil_generator.hpp>
#include <string>

namespace m2 {
namespace routing {

struct UserInfo
{
  boost::uuids::uuid guid;
  std::string domain;

  UserInfo();
  ~UserInfo();
  UserInfo(boost::uuids::uuid guid, std::string domain);

  inline bool isNil() {
      return guid.is_nil();
  }
};

}
}
