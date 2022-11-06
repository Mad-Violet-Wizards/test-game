#include <fstream>
#include <format>
#include <chrono>

#include "LogFileManager.hpp"
#include "ConsoleLog.hpp"

std::unique_ptr<LogFileManager> LogFileManager::s_instance = nullptr;

LogFileManager::LogFileManager()
{
  CreateLogDirectory();
  CreateLogFile();
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
  if (s_instance == nullptr)
  {
    CONSOLE_LOG_ERROR("[LogFileManager] Instance of LogsFileManager is null.");
  }

  const std::string logsDirectory   = "../logs/";

  if (!std::filesystem::exists(logsDirectory))
  {
    CONSOLE_LOG_INFO("[LogFileManager] Creating logs/ directory.");

    bool success = std::filesystem::create_directories(logsDirectory);

    if (success) { std::cout << "[LogFileManager][Info] Created logs directory.\n"; }
    else         { std::cout << "[LogFileManager][Error] Cannot create logs directory.\n"; }  }
}

void LogFileManager::CreateLogFile()
{
  if (s_instance == nullptr)
  {
    CONSOLE_LOG_ERROR("[LogFileManager] Instance of LogsFileManager is null.");
  }

  if (m_pathToLogFile.empty() == false)
  {
    return;
  }

  auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

  const std::string timeFileName = std::format("{:%Y-%m-%d-%H-%M-%S-log.txt}",
                                               std::chrono::floor<std::chrono::seconds>(time));

  std::string timeFilePath = std::format("{}{}", "../logs/", timeFileName);

  std::ofstream timeFile(timeFilePath);
  timeFile.close();

  LogFileManager::m_pathToLogFile = std::move(timeFilePath);
}

const std::string &LogFileManager::GetLogFilePath() const
{
  return m_pathToLogFile;
}
