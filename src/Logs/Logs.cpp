#include "Logs.hpp"

#include <iostream>
#include <filesystem>
#include <fstream>

Logs::Logs() {}

Logs::~Logs() {}

void Logs::Init()
{
    std::cout << "Init method\n";
    m_timestamp = m_dt.GetCurrentTimestamp();
    
    if (!std::filesystem::exists("../Log/"))
    {
        std::cout << "[Onyx Core] Didn't found Log directory. Creating\n";
        std::filesystem::create_directory("../Log");
    }
    else
    {
        std::cout << "[Onyx Core] Found Log directory.\n";
    }

    m_currentLogFile = "../Log/Log_" + std::to_string(m_timestamp) + ".txt";
    std::ofstream logFile(m_currentLogFile);



}