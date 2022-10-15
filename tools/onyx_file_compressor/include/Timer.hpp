#pragma once

#include <chrono>

class Timer
{

public:

    Timer() = default;
    ~Timer() = default;

    void Start();
    void End();
    
    double ElapsedTime() const;

private:

    std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
    std::chrono::time_point<std::chrono::high_resolution_clock> m_end;

};