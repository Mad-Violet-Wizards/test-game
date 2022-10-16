#pragma once

#include <chrono>
#include <iostream>

namespace OnyxTools
{
    namespace Compressor
    {
        template <typename ...Args>
        constexpr void LOG(Args &&...args)
        {
            auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

            std::cout << std::format("[{:%Y/%m/%d %H:%M:%S}]", std::chrono::floor<std::chrono::milliseconds>(time)) << " ";
            ((std::cout << std::forward<Args>(args) << " "), ...);
            std::cout << "\n" << std::flush;
        }
    }
}