#include "utils/Config.h"

namespace m2 {
namespace routing {

int Config::alpha = 3;
int Config::k = 20;
boost::posix_time::time_duration Config::response_timeout = boost::posix_time::millisec(500);

} // namespace routing
} // namespace m2
