#pragma once

#include <fstream>
#include "../Time/DateTime.hpp"

static std::string g_currentLogFileName = "";

class Logs
{

public:
    Logs();
    ~Logs();
    
    void WriteToFile(std::string t);

private:
    void Init();
    std::string DateTimePrefix();

    std::ofstream m_logFile;
};