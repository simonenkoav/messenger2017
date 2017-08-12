#include "../stdafx.h"
#include "core/Node.h"
#include "kbuckets/KBucketsTools.h"

#include "easyloggingpp_v9.95.0/easylogging++.h"

INITIALIZE_EASYLOGGINGPP

int main()
{
    el::Configurations conf("../../configs/log_conf.conf");
    el::Loggers::reconfigureLogger("default", conf);
    LOG(DEBUG) << "My first info log using default logger";
    return 0;
}
