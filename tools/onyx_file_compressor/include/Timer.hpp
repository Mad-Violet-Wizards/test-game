#pragma once

#include <chrono>

namespace OnyxTools
{
    namespace Compressor
    {
        class Timer
        {
        public:

            Timer() = default;
            ~Timer() = default;

            void Start();
            void End();

            [[nodiscard]] double ElapsedTime() const;

        private:

            std::chrono::time_point<std::chrono::high_resolution_clock> m_start;
            std::chrono::time_point<std::chrono::high_resolution_clock> m_end;
        };
    }
}