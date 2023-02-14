#include "LogFileManager.hpp"

std::unique_ptr<LogFileManager> LogFileManager::s_instance = nullptr;

LogFileManager::LogFileManager()
{
  CreateLogDirectory();
}

LogFileManager::~LogFileManager() { }

LogFileManager &LogFileManager::GetInstance()
{
  if (LogFileManager::s_instance == nullptr)
  {
    LogFileManager::s_instance = std::unique_ptr<LogFileManager>(new LogFileManager);
  }

  return *s_instance;
}

void LogFileManager::CreateLogDirectory()
{
  const std::string logsDirectory   = "../logs";

  if (!std::filesystem::exists(logsDirectory))
  {
    CONSOLE_LOG_INFO("[LogFileManager] Creating logs/ directory.");

    bool success = std::filesystem::create_directories(logsDirectory);

    if (success) { std::cout << "[LogFileManager][Info] Created logs directory.\n"; }
    else         { std::cout << "[LogFileManager][Error] Cannot create logs directory.\n"; }  }
}

void LogFileManager::CreateLogFile(const std::string &fileName)
{
  const std::string logFilePath { "../logs/" + fileName };

  m_logFiles.insert( { fileName, logFilePath} );

  std::ofstream logFile(logFilePath);
 
  logFile.close();
}

const std::string &LogFileManager::GetLogFilePath(const std::string &fileName) const
{
  return m_logFiles.at(fileName);
}

bool LogFileManager::DoesLogFileExists(const std::string &logFile) const
{
  if (m_logFiles.find(logFile) != m_logFiles.end())
  {
    return true;
  }

  return false;
}