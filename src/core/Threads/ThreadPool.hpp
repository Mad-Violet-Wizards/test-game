#pragma once


#include "ThreadTask.hpp"

class ThreadPool
{
  
  public:

    explicit ThreadPool(unsigned int threadsNumber = std::thread::hardware_concurrency());
    ~ThreadPool();

    ThreadPool(const ThreadPool &other) = delete;
    ThreadPool(const ThreadPool &&other) = delete;

    ThreadPool &operator=(const ThreadPool& other) = delete;
    ThreadPool &operator=(const ThreadPool&& other) = delete;

    void Submit(std::unique_ptr<ThreadTask> &&task);

    template<typename F, typename ...Args>
    void Submit(F&& f, Args&&... args)
    {
      auto task = std::make_unique<ThreadTask>();

      task -> Assign(f, args...);

      Submit(std::move(task));
    }

    void Start();
    void Shutdown();

    bool IsRunning() const;

  private:

    std::vector<std::unique_ptr<sf::Thread>> m_threads;
    std::vector<std::unique_ptr<ThreadTask>> m_tasks;
};