#include "ThreadPoolSFML.hpp"

int ThreadPoolSFML::s_jobsFinished = 0;
int ThreadPoolSFML::s_totalJobs = 0;

ThreadPoolSFML::ThreadPoolSFML(unsigned int threadsNumber)
{
  m_threads.reserve(threadsNumber);
  m_threads.shrink_to_fit();
}

void ThreadPoolSFML::Process()
{
  while (!m_queue.Empty())
  {
    auto func = m_queue.Dequeue();

    std::unique_ptr<sf::Thread> thread(new sf::Thread(func));

    m_threads.push_back(std::move(thread));
  }

  for (auto &thread : m_threads)
  {
    thread->launch();
  }
}

void ThreadPoolSFML::Clear()
{
  m_threads.clear();
}