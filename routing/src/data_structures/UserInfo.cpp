#include "data_structures/UserInfo.h"

using namespace m2::routing;

UserInfo::UserInfo(boost::uuids::uuid guid, std::string domain)
    : guid(guid), domain(domain) {}

UserInfo::UserInfo() : guid(boost::uuids::nil_uuid()), domain(std::string()) {}

UserInfo::~UserInfo()
{
}