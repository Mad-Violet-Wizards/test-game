#include "DateTime.hpp"

#include <iostream>

DateTime::DateTime() : m_time(std::time(0))
{
}

std::string DateTime::GetCurrentDate() const
{
    std::tm* now = std::localtime(&m_time);

    std::string CurrentDate(
        std::to_string(now -> tm_year + 1900) + "-"
        + std::to_string(now -> tm_mon + 1) + "-"
        + std::to_string(now -> tm_mday)
    );

    return CurrentDate;
}

std::string DateTime::GetCurrentTime() const
{
    std::tm* now = std::localtime(&m_time);

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

DateTime::~DateTime() {}

