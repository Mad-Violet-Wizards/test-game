#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "ThreadSafe_Queue.hpp"

/*
Please do not use this ThreadPool, for some reason using std::thread instead of sf::Thread
causes some OpenGL errors, I don't know why, but I'm not going to spend more time on this.
Use ThreadPoolSFML instead.
*/

class ThreadPool
{
  public:

    explicit ThreadPool(unsigned int threadsNumber = std::thread::hardware_concurrency());
    ~ThreadPool();

    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool(ThreadPool &&other) = delete;
    
    ThreadPool &operator=(const ThreadPool &other) = delete;
    ThreadPool &operator=(ThreadPool &&other) = delete;

    template<typename F, typename... Args>
    auto Make_Function(F&& f, Args&&... args)
    {
      return std::function{[f, args...](){ return f(args...); }};
    }

    template <typename F, typename... Args>
    void Submit(F&& f, Args&&... args)
    {
      {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_jobsPending++;

        m_queue.Push(Make_Function(f, args...));
      }

      m_condition.notify_one();
    }

    void Shutdown();

    bool DoesFinished();

    void WaitForFinish();

  public:

    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::atomic<int> m_jobsPending;

    std::vector<std::thread> m_threads;

    ThreadSafe::Queue<std::function<void()>> m_queue;

    bool m_shutdown;

};