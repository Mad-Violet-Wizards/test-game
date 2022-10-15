#include "Timer.hpp"

#include "Log.hpp"

void Timer::Start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

void Timer::End()
{
    m_end = std::chrono::high_resolution_clock::now();
}

double Timer::ElapsedTime() const
{
    return std::chrono::duration<double, std::milli>(m_end - m_start).count();
}