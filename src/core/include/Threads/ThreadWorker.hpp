#pragma once

class ThreadPool;

class ThreadWorker
{
  public:

    ThreadWorker(ThreadPool* pool);
    ~ThreadWorker() = default;

    void operator()();

  private:
  
      ThreadPool* m_pool;
};