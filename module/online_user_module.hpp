#pragma once
#include<websocketpp/server.hpp>
#include<websocketpp/config/asio_no_tls.hpp>
#include"Thread.hpp"
#include<unordered_map>
namespace online_user_module
{
    using websocket_server=websocketpp::server<websocketpp::config::asio>;
    using connect=websocket_server::connection_ptr;
    class online_users
    {
    public:
    void enter_gamelobby(int id,const connect& con)
    {
        _mutex.lock();
        _globby.insert(std::make_pair(id,con));
    }
    void exit_gamelobby(int id)
    {
        _mutex.lock();
        _globby.erase(id);
    }
    void enter_gameroom(int id,const connect& con)
    {
        _mutex.lock();
        _groom.insert(std::make_pair(id,con));
    }
    void exit_gameroom(int id)
    {
        _mutex.lock();
        _globby.erase(id);
    }
    bool in_globy(int id)
    {
        _mutex.lock();
        return _globby.count(id);
    }
    bool in_room(int id)
    {
        _mutex.lock();
        return _groom.count(id);
    }
    connect get_in_giobby(int id)
    {
        _mutex.lock();
        if(!_globby.count(id)) return nullptr;
        return _globby[id];
    }
    connect get_in_groom(int id)
    {
        _mutex.lock();
        if(!_groom.count(id)) return nullptr;
        return _groom[id];
    }
    private:
        std::unordered_map<int,connect> _globby; 
        std::unordered_map<int,connect> _groom;
        Thread_util::auto_mutex _mutex;
    };
};