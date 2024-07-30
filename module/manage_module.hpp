#pragma once
#include"Thread.hpp"
#include"log.hpp"
#include"mysql.hpp"
namespace manage_module
{
    constexpr int BUFFSIZE=1024;
    const char* ADDUSER="insert into user (username,password) value('%s','%s')";
    const char* FIND_NAME="select * from user where username='%s'";
    const char* FIND="select * from user where username='%s'and password='%s'";
    const char* WIN="update user set win_count=win_count+1 where username='%s'";
    const char* COUNT="update user set total_count=total_count+1 where username='%s'";
    struct user
    {
        using ptr=std::shared_ptr<user>;

        int _id;
        std::string _name;
        std::string _password;
        int _score;
        int _total_count;
        int _win_count;
    };
    class user_table
    {
    public:
        user_table()
        {}
        bool insert(const std::string& name,const std::string& password)
        {
            char buff[BUFFSIZE];
            snprintf(buff,BUFFSIZE,ADDUSER,name.c_str(),password.c_str());
            std::string s=_root.exec(buff);
            if(s=="-1") return false;
            return true;
        }
        bool find_name(const std::string& name)
        {
            char buff[BUFFSIZE]={0};
            snprintf(buff,BUFFSIZE,FIND_NAME,name.c_str());
            std::string s=_root.exec(buff);
            if(s==""||s=="-1") return false;
            return true;
        }
        user::ptr login(const std::string& name,const std::string& password)
        {
            char buff[BUFFSIZE]={0};
            snprintf(buff,BUFFSIZE,FIND,name.c_str(),password.c_str());
            std::string s=_root.exec(buff);
            if(s=="-1"||s=="") return nullptr;
            std::istringstream is(s);
            user::ptr p=std::make_shared<user>();
            is>>p->_id>>p->_name>>p->_password>>p->_score>>p->_total_count>>p->_win_count;
            return p;
        }
        bool add_count(const std::string& name)
        {
            char buff[BUFFSIZE]={0};
            snprintf(buff,BUFFSIZE,COUNT,name.c_str());
            std::string s=_root.exec(buff);
            if(s=="-1") return false;
            return true;
        }
        bool win(const std::string& name)
        {
            if(!add_count(name)) return false;
            char buff[BUFFSIZE]={0};
            snprintf(buff,BUFFSIZE,WIN,name.c_str());
            std::string s=_root.exec(buff);
            if(s=="-1") return false;
            return true;
        }
    private:
        mysql_util::mysql _root;
};

}