#include "Logs.hpp"

#include <filesystem>

Logs::Logs() 
{
    Init();
}

Logs::~Logs() {}

void Logs::Init()
{    
    if (!std::filesystem::exists("../Log/"))
    {
        std::cout << "[Onyx Core] Didn't found Log directory. Creating\n";
        std::filesystem::create_directory("../Log");
    }
    else
    {
        std::cout << "[Onyx Core] Found Log directory.\n";
    }


    if (g_currentLogFileName.empty())
    {
        g_currentLogFileName = "../../Log/Log_" + DateTime::GetCurrentDateAndTime() + ".txt";
        m_logFile.open(g_currentLogFileName, std::ios_base::app);
        m_logFile << DateTimePrefix()
                  << "[Onyx Core] Initialized Logs class with .txt file.\n";
    }

    m_logFile.close();
}

std::string Logs::DateTimePrefix()
{
    std::string _temp = "[" + DateTime::GetCurrentDateAndTime() + "]";
    return _temp;
}

Logs &Logs::operator<<(const char* value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << DateTimePrefix()
            << " "
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs &Logs::operator<<(const std::string& value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << DateTimePrefix()
            << " "
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs& Logs::operator<<(const int value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << DateTimePrefix()
            << " "
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs& Logs::operator<<(const double value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << DateTimePrefix()
            << " "
            << value << "\n";

  m_logFile.close();
  return *this;
}
