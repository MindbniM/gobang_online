#include"manage_module.hpp"
#include"room_module.hpp"
int main()
{
    //using enum Log_util::log_level;
    //ADD_APPENDER_STDOUT(DEBUG);
    chess_message c;
    c.result=1;
    c.row=2;
    c.col=1;
    c.user_id=2;
    c.re="对方掉线";
    std::string str=c.serialize();
    std::cout<<str<<std::endl;
    chess_message temp;
    temp.Deserialize(str);
    std::cout<<temp.result<<std::endl;
    std::cout<<temp.row<<std::endl;
    std::cout<<temp.col<<std::endl;
    std::cout<<temp.user_id<<std::endl;
    std::cout<<temp.re<<std::endl;
    return 0;
}