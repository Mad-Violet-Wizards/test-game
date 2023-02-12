#include "ThreadTask.hpp"
#include "ConsoleLog.hpp"

ThreadTask::ThreadTask()
{
  m_finished = false;
}

void ThreadTask::Run()
{
  sf::Lock lock(m_mutex);
  
  m_task();
  m_finished = true;
}

bool ThreadTask::IsFinished() const
{
  sf::Lock lock(m_mutex);

  return m_finished;
}