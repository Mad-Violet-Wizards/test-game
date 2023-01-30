#include "Timer.hpp"

void Timer::Start()
{
  m_startTime = std::chrono::high_resolution_clock::now();
}

void Timer::Stop()
{
  m_endTime = std::chrono::high_resolution_clock::now();
}

void Timer::Reset()
{
  m_startTime = std::chrono::high_resolution_clock::now();
  m_endTime = std::chrono::high_resolution_clock::now();
}