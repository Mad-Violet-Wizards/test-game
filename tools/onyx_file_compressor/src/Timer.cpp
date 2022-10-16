#include "Timer.hpp"

#include "Log.hpp"

void OnyxTools::Compressor::Timer::Start()
{
    m_start = std::chrono::high_resolution_clock::now();
}

void OnyxTools::Compressor::Timer::End()
{
    m_end = std::chrono::high_resolution_clock::now();
}

double OnyxTools::Compressor::Timer::ElapsedTime() const
{
    return std::chrono::duration<double, std::milli>(m_end - m_start).count();
}