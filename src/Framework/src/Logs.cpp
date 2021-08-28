#include <filesystem>

#include "Logs.hpp"
#include "Prefixes.hpp"

Logs::Logs() 
{
    Init();
}

Logs::~Logs() {}

void Logs::Init()
{    
    if (!std::filesystem::exists("../../log/"))
    {
        std::cout << Prefixes::OnyxCorePrefix()
                  << "Didn't found Log directory. Creating\n";

        std::filesystem::create_directory("../../log");
    }
    else
    {
        std::cout << Prefixes::OnyxCorePrefix()
                  << "Found Log directory.\n";
    }


    if (g_currentLogFileName.empty())
    {
        g_currentLogFileName = "../../log/Log_" + DateTime::GetCurrentDateAndTime() + ".txt";
        m_logFile.open(g_currentLogFileName, std::ios_base::app);
        m_logFile << Prefixes::DateTimePrefix()
                  << Prefixes::OnyxCorePrefix()
                  << "Initialized Logs class with .txt file.\n";
    }

    m_logFile.close();
}

Logs &Logs::operator<<(const char* value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << Prefixes::DateTimePrefix()
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs &Logs::operator<<(const std::string& value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << Prefixes::DateTimePrefix()
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs& Logs::operator<<(const int value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << Prefixes::DateTimePrefix()
            << value << "\n";

  m_logFile.close();
  return *this;
}

Logs& Logs::operator<<(const double value)
{
  m_logFile.open(g_currentLogFileName, std::ios_base::app);

  m_logFile << Prefixes::DateTimePrefix()
            << value << "\n";

  m_logFile.close();
  return *this;
}
