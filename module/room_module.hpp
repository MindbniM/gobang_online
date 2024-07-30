#pragma once
#include <vector>
#include "manage_module.hpp"
#include<jsoncpp/json/json.h>
struct chess_message
{
#define JSONADD(json,data) do { json[#data]=data;}while(0)
    using ptr = std::shared_ptr<chess_message>;
    std::string serialize()    
    {
        Json::Value v;
        JSONADD(v,result);
        JSONADD(v,user_id);
        JSONADD(v,row);
        JSONADD(v,col);
        JSONADD(v,re);
        JSONADD(v,winner);
        Json::FastWriter w;
        return  w.write(v);
    }
    void Deserialize(const std::string& str)
    {
        Json::Reader r;
        Json::Value root; 
        if(!r.parse(str,root)) return ;
        result=root["result"].asInt();
        user_id=root["user_id"].asInt();
        row=root["row"].asInt();
        col=root["col"].asInt();
        re=root["re"].asString();
        winner=root["winner"].asInt();
    }
    int result=-1;  // 表示此次请求是否正常完成
    int user_id=-1; // 表示这次请求的用户id
    int row=-1;
    int col=-1;
    std::string re; // 返回的信息
    int winner=0;
};
namespace room_module
{
    enum class r_status
    {
        START = 1,
        OVER
    };
#define BOARD_ROW 15
#define BOARD_COL 15

    // 返回的请求
    class room
    {
    public:
        room(int room_id, manage_module::user_table &root) : _id(room_id), _b(root), _g(BOARD_ROW, std::vector<int>(BOARD_COL))
        {
            using enum Log_util::log_level;
            int n = rand() % 2;
            if (n == 0)
            {
                std::swap(_uwid, _ubid);
            }
            LOG(INFO, "room create success id:%d", _id);
        }
        void add_write_user(int id)
        {
            _uwid = id;
            _count++;
        }
        void add_black_user(int id)
        {
            _ubid = id;
            _count++;
        }
        std::string handle_chess(const std::string& jsonstr)
        {
            
        }
        ~room()
        {
            LOG(Log_util::log_level::INFO, "room delete id:%d", _id);
        }

    private:
        int _id;
        r_status _stu;
        int _uwid = -1;
        int _ubid = -1;
        int _count = 0;
        std::vector<std::vector<int>> _g;
        manage_module::user_table &_b;
    };
};