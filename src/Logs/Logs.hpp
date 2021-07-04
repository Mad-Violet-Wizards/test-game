#pragma once

#include "../Time/DateTime.hpp"

class Logs
{

public:
    Logs();
    ~Logs();
    
    void Init();

private:
    DateTime m_dt;
    int m_timestamp;
    std::string m_currentLogFile;
};