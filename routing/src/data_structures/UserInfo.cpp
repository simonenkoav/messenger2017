#include "data_structures/UserInfo.h"


UserInfo::UserInfo(boost::uuids::uuid uuid, std::string domain)
  : uuid(uuid), domain(domain) {}

UserInfo::~UserInfo()
{
}