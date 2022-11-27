#pragma once

#include <functional>
#include <mutex>
#include <thread>
#include <vector>

#include "ThreadSafe_Queue.hpp"

class ThreadPool
{
  public:

    explicit ThreadPool(unsigned int threadsNumber = std::thread::hardware_concurrency());
    ~ThreadPool();

    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool(ThreadPool &&other) = delete;
    
    ThreadPool &operator=(const ThreadPool &other) = delete;
    ThreadPool &operator=(ThreadPool &&other) = delete;

    template <typename F, typename... Args>
    void Submit(F&& f, Args&&... args)
    {
      {
        std::unique_lock<std::mutex> lock(m_mutex);
        m_jobsPending++;

        std::function<decltype(f(args...))()> job = std::bind(std::forward<F>(f), std::forward<Args>(args)...);

        std::function<void()> wrapperJob = [job]()
        {
          job();
        };

        m_queue.Push(wrapperJob);
      }

      m_condition.notify_one();
    }

    void Shutdown();

    void WaitForFinish();

  public:

    std::mutex m_mutex;
    std::condition_variable m_condition;
    std::atomic<int> m_jobsPending;

    std::vector<std::thread> m_threads;

    OnyxCore::Containers::ThreadSafe::Queue<std::function<void()>> m_queue;

    bool m_shutdown;

};