#pragma once


class FpsCounter
{

public:

  ~FpsCounter();

  static FpsCounter &GetInstance();

  void CalculateFramesPerSecond(float deltaTime);

  float GetFps() const;

private:

  FpsCounter();

private:

  static std::unique_ptr<FpsCounter> s_instance;

  float m_fps;

};