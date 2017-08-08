#pragma once
#include <boost/date_time/posix_time/posix_time_duration.hpp>

namespace m2 {
namespace routing {
/// Constants is a singleton for providing all global constants
/// TODO: implement method updateConfig (string filename)
class Config
{
public:
    Config() {
        setDefaultConfig();
    }

public:
    static int getAlpha() {
        return alpha;
    }

    static int getK() {
        return k;
    }

    static boost::posix_time::time_duration getResponseTimeout() {
        return response_timeout;
    }

private:
    static int alpha;
    static int k;
    static boost::posix_time::time_duration response_timeout;

  static void setDefaultConfig(){
      // for now, do nothing
  }

};

} // namespace routing
} // namespace m2
