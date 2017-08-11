#include "data_structures/UserInfo.h"

using namespace m2::routing;

UserInfo::UserInfo(boost::uuids::uuid uuid, std::string domain)
    : uuid(uuid), domain(domain) {}

UserInfo::UserInfo() : uuid(boost::uuids::nil_uuid()), domain(std::string()){}

UserInfo::~UserInfo() 
{
}