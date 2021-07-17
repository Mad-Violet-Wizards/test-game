#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "../Time/DateTime.hpp"

static std::string g_currentLogFileName = "";

class Logs
{

public:
    Logs();
    ~Logs();
    
    Logs& operator<<(const char* value);
    Logs& operator<<(const std::string& value);
    Logs& operator<<(const int value);
    Logs& operator<<(const double value);

private:
    void Init();
    
    std::string DateTimePrefix();

    std::ofstream m_logFile;
};