#include "DateTime.hpp"

#include <iostream>
#include <chrono>

DateTime::DateTime() {}

std::string DateTime::GetCurrentDate() const
{
    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);

    std::string CurrentDate(
        std::to_string(now -> tm_year + 1900) + "-"
        + std::to_string(now -> tm_mon + 1) + "-"
        + std::to_string(now -> tm_mday)
    );

    return CurrentDate;
}

std::string DateTime::GetCurrentTime() const
{
    std::time_t time = std::time(0);
    std::tm* now = std::localtime(&time);

    std::string CurrentTime(
        std::to_string(now -> tm_hour) + ":"
        + std::to_string(now -> tm_min) + ":"
        + std::to_string(now -> tm_sec)
    );

    return CurrentTime;
}

std::string DateTime::GetCurrentDateAndTime() const
{
    std::string CurrentDateAndTime(
        GetCurrentDate() + " " + GetCurrentTime()
    );

    return CurrentDateAndTime;
}

int DateTime::GetCurrentTimestamp() const
{
    const auto p1 = std::chrono::system_clock::now();
    
    return std::chrono::duration_cast<std::chrono::seconds>(p1.time_since_epoch()).count();
}

DateTime::~DateTime() {}

