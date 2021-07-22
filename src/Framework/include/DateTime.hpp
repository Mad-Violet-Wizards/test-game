#pragma once

#include <ctime>
#include <string>

namespace DateTime
{
    std::string GetCurrentDate();
    std::string GetCurrentTime();
    std::string GetCurrentDateAndTime();

    int GetCurrentTimestamp();

};
