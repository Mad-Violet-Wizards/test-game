#include "ThreadPool.hpp"

ThreadPool::ThreadPool(unsigned int threadsNumber)
{
  m_threads.reserve(threadsNumber);
  m_tasks.reserve(threadsNumber);
}

ThreadPool::~ThreadPool()
{
  Shutdown();
}

void ThreadPool::Submit(std::unique_ptr<ThreadTask> &&task)
{
  std::unique_ptr<sf::Thread> thread(new sf::Thread(&ThreadTask::Run, task.get()));

  m_tasks.push_back(std::move(task));

  m_threads.push_back(std::move(thread));
}

void ThreadPool::Start()
{
  for (auto &thread : m_threads)
  {
    thread -> launch();
  }
}

void ThreadPool::Shutdown()
{
  for (auto &thread : m_threads)
  {
    thread -> wait();
  }

  m_threads.clear();
  m_tasks.clear();
}

bool ThreadPool::IsRunning() const
{
  return std::any_of(m_tasks.begin(), m_tasks.end(), [](auto &task) { return task -> IsFinished() == false; });
}