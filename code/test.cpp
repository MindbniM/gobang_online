#include"util/log.hpp"
#include"util/Thread.hpp"
#include<unistd.h>
void test()
{
    using enum Log_util::log_level;
    while(1)
    {
        LOG(DEBUG,"thread is...running ");
        sleep(1);
    }
}
int main()
{
    ADD_APPENDER_STDOUT(Log_util::log_level::DEBUG);
    Thread_util::Thread t1(test);
    Thread_util::Thread t2(test);
    t1.join();
    t2.join();

    return 0;
}
