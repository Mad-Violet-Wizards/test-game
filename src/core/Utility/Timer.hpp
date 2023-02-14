#pragma once


template<typename T>
concept Chrono = requires(T a)
{
    { std::chrono::duration_cast<T>(a) };
};

class Timer
{

  public:

    Timer() = default;
    ~Timer() = default;

    Timer(const Timer &) = delete;
    Timer(Timer &&) = delete;

    Timer &operator=(const Timer &) = delete;
    Timer &operator=(Timer &&) = delete;

    void Start();
    void Stop();
    void Reset();

    template <Chrono C>
    float GetElapsedTime() const
    {
      return std::chrono::duration_cast<C>(m_endTime - m_startTime).count();
    }

  private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_startTime;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_endTime;

};