#include"log.hpp"
#include<pthread.h>
using namespace Log;
int main()
{
    ADD_APPENDER_STDOUT(log_level::DEBUG);
    ADD_APPENDER_FILEOUT(log_level::DEBUG,"log.txt");
    LOG(log_level::DEBUG,"fuck-%s","you");
    //logger::get_logger()->log(event);
    return 0;
}