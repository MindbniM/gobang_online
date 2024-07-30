#pragma once
#include <iostream>
#include <functional>
#include <memory>
#include <pthread.h>
#include <semaphore.h>
#include <cstring>
#include "log.hpp"
namespace Thread_util
{
    using _func_type_ = std::function<void()>;
    class Thread
    {
    public:
        Thread()
        {
        }
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
        pthread_t _id;
    };
    template <class Fn, class... Args>
    Thread::Thread(Fn f, Args &&...args)
    {
        using enum Log_util::log_level;
        _func_type_ *_func = new _func_type_(std::bind(std::forward<Fn>(f), std::forward<Args>(args)...));
        int n = pthread_create(&_id, nullptr, func, (void *)_func);
        if (n != 0)
        {
            LOG(ERROR, "Thread create error %d", n);
        }
    }
    void *Thread::func(void *ptr)
    {
        _func_type_ *p = static_cast<_func_type_ *>(ptr);
        (*p)();
        delete p;
        return nullptr;
    }
}

namespace Thread_util
{
    class Sem
    {
    public:
        using enum Log_util::log_level;
        Sem(uint32_t count)
        {
            int n = sem_init(&_sem, 0, count);
            if (n < 0)
                LOG(ERROR, "sem init error %s", strerror(errno));
        }
        void post()
        {
            int n = sem_post(&_sem);
            if (n < 0)
                LOG(ERROR, "sem post error %s", strerror(errno));
        }
        void wait()
        {
            int n = sem_wait(&_sem);
            if (n < 0)
                LOG(ERROR, "sem wait error %s", strerror(errno));
        }
        ~Sem()
        {
            sem_destroy(&_sem);
        }

    private:
        sem_t _sem;

        Sem(const Sem &s) = delete;
        Sem &operator=(const Sem &s) = delete;
    };
}

namespace Thread_util
{
    class Spinlock
    {
    public:
        Spinlock()
        {
            pthread_spin_init(&_mutex, 0);
        }

        ~Spinlock()
        {
            pthread_spin_destroy(&_mutex);
        }

        void lock()
        {
            pthread_spin_lock(&_mutex);
        }

        void unlock()
        {
            pthread_spin_unlock(&_mutex);
        }

    private:
        pthread_spinlock_t _mutex;
    };

}

namespace Thread_util
{
    class mutex
    {
    public:
        mutex()
        {
            pthread_mutex_init(&_mutex, 0);
        }

        ~mutex()
        {
            pthread_mutex_destroy(&_mutex);
        }

        void lock()
        {
            pthread_mutex_lock(&_mutex);
        }

        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }

    private:
        pthread_mutex_t _mutex;
    };

}

namespace Thread_util
{
    class rwlock
    {
    public:
        rwlock()
        {
            pthread_rwlock_init(&_mutex, 0);
        }

        ~rwlock()
        {
            pthread_rwlock_destroy(&_mutex);
        }

        void rlock()
        {
            pthread_rwlock_rdlock(&_mutex);
        }
        void wlock()
        {
            pthread_rwlock_wrlock(&_mutex);
        }

        void unlock()
        {
            pthread_rwlock_unlock(&_mutex);
        }

    private:
        pthread_rwlock_t _mutex;
    };

}

namespace Thread_util
{
    class auto_mutex
    {
    public:
        auto_mutex()
        {
            pthread_mutex_init(&_mutex, 0);
        }

        void lock()
        {
            pthread_mutex_lock(&_mutex);
        }
        ~auto_mutex()
        {
            unlock();
            pthread_mutex_destroy(&_mutex);
        }
    private:

        void unlock()
        {
            pthread_mutex_unlock(&_mutex);
        }
        pthread_mutex_t _mutex;
    };

}
