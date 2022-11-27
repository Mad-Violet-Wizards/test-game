#include "ThreadPool.hpp"

#include "ThreadWorker.hpp"
#include "ConsoleLog.hpp"

ThreadPool::ThreadPool(unsigned int threadsNumber)
  : m_jobsPending(0)
  , m_threads(std::vector<std::thread>(threadsNumber))
  , m_shutdown(false)
{
  for (auto& thread : m_threads)
  {
    m_threads.emplace_back(std::thread(ThreadWorker(this)));
  }
}

ThreadPool::~ThreadPool()
{
  Shutdown();
}

void ThreadPool::Shutdown()
{
  m_shutdown = true;

  m_condition.notify_all();

  for (std::thread &t : m_threads)
  {
    if (t.joinable())
    {
      t.join();
    }
  }
}

void ThreadPool::WaitForFinish()
{
  std::unique_lock<std::mutex> lock(m_mutex);
  m_condition.wait(lock);
}