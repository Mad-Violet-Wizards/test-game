#pragma once

#include <SFML/Graphics.hpp>

#include "ThreadSafe_Queue.hpp"

#include <thread>
#include <mutex>
#include <vector>
#include <functional>

class ThreadPoolSFML
{

  public:

    explicit ThreadPoolSFML(unsigned int threadsNumber = std::thread::hardware_concurrency());
    ~ThreadPoolSFML() = default;

    ThreadPoolSFML(const ThreadPoolSFML &other) = delete;
    ThreadPoolSFML(ThreadPoolSFML &&other) = delete;

    ThreadPoolSFML &operator=(const ThreadPoolSFML &other) = delete;
    ThreadPoolSFML &operator=(ThreadPoolSFML &&other) = delete;

    template<typename F, typename... Args>
    auto Make_Function(F&& f, Args&&... args)
    {
      return std::function
      {
          [f, args...](){ return f(args...); }
      };
    }

    template <typename F, typename... Args>
    void Submit(F &&f, Args &&...args)
    {
        m_mutex.lock();

        m_queue.Push(Make_Function(f, args...));

        m_mutex.unlock();
    }

    void Process();

    void Clear();

  public:

      static int s_jobsFinished;
      static int s_totalJobs;

  private:

    sf::Mutex m_mutex;

    ThreadSafe::Queue<std::function<void()>> m_queue;
    std::vector<std::unique_ptr<sf::Thread>> m_threads;

};