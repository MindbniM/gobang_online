#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <pthread.h>
#include"log.hpp"
namespace Thread_util
{
    using _func_type_ =std::function<void()>;
    class Thread
    {
    public:
        Thread()
        {}
        template <class Fn, class... Args>
        Thread(Fn f, Args &&...args);
        pthread_t get_id()
        {
            return _id;
        }
        static pthread_t get_self_id()
        {
            return pthread_self();
        }
        int join()
        {
            return pthread_join(_id, nullptr);
        }
        int detach()
        {
            return pthread_detach(_id);
        }
        void exit()
        {
            pthread_exit(nullptr);
        }
        static void *func(void *ptr);

    private:
        std::string _name;
        pthread_t _id;
    };
    template <class Fn, class... Args>
    Thread::Thread(Fn f, Args &&...args)
    {
        using enum Log_util::log_level;
        _func_type_* _func =new _func_type_(std::bind(std::forward<Fn>(f),std::forward<Args>(args)...));
        int n=pthread_create(&_id,nullptr,func,(void*)_func);
        if(n!=0)
        {
            LOG(ERROR,"Thread create error %d",n);
        }
    }
    void *Thread::func(void *ptr)
    {
        _func_type_* p=static_cast<_func_type_*>(ptr);
        (*p)();
        delete p;
        return nullptr;
    }
}
