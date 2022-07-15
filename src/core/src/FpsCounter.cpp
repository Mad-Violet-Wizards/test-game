#include <cmath>
#include <iostream>

#include "FpsCounter.hpp"

std::unique_ptr<FpsCounter> FpsCounter::s_instance = nullptr;

FpsCounter::FpsCounter() 
  : m_fps(0.f) { }

FpsCounter::~FpsCounter() { }

FpsCounter &FpsCounter::GetInstance()
{
  if (FpsCounter::s_instance == nullptr)
  {
    FpsCounter::s_instance = std::unique_ptr<FpsCounter>(new FpsCounter);
  }

  return *s_instance;
}

void FpsCounter::CalculateFramesPerSecond(float deltaTime)
{
  m_fps = std::floor(1.f / deltaTime);
}

float FpsCounter::GetFps() const
{
  return m_fps;
}