#include "ThreadWorker.hpp"

#include "ThreadPool.hpp"

#include <mutex>
#include <functional>

ThreadWorker::ThreadWorker(ThreadPool* pool)
  : m_pool(pool)
{

}

void ThreadWorker::operator()()
{
  std::function<void()> f;

  while (true)
  {
    {
      std::unique_lock<std::mutex> lock(m_pool -> m_mutex);

      while (!m_pool -> m_shutdown && m_pool -> m_queue.Empty())
      {
        m_pool -> m_condition.wait(lock);
      }

      if (m_pool -> m_shutdown)
      {
        return;
      }

      f = m_pool -> m_queue.Front();
      m_pool -> m_queue.Pop();
    }

    f();

    if (--m_pool -> m_jobsPending == 0)
    {
      m_pool -> m_condition.notify_all();
    }
  }
}