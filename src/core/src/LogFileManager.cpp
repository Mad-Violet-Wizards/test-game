#include <fstream>
#include <format>

#include "LogFileManager.hpp"

std::unique_ptr<LogFileManager> LogFileManager::s_instance = nullptr;

LogFileManager::LogFileManager() { }

LogFileManager::~LogFileManager() { }

LogFileManager &LogFileManager::GetInstance()
{
  if (LogFileManager::s_instance == nullptr)
  {
    LogFileManager::s_instance = std::unique_ptr<LogFileManager>(new LogFileManager);
  }

  return *s_instance;
}

void LogFileManager::GenerateLogDirectory()
{
  if (s_instance == nullptr)
  {
    std::cout << "[LogFileManager][Error] Instance of LogsFileManager does not exists.\n";
  }

  const std::string logsDirectory   = "../logs/";

  if (std::filesystem::exists(logsDirectory))
  {
    std::cout << "[LogFileManager][Info] Logs directory found.\n";
  }
  else
  {
    std::cout << "[LogFileManager][Info] Logs directory does not exists. Creating.\n";

    bool success = std::filesystem::create_directories(logsDirectory);

    if (success) { std::cout << "[LogFileManager][Info] Created logs directory.\n"; }
    else          { std::cout << "[LogFileManager][Error] Cannot create logs directory.\n"; }
  }
}

void LogFileManager::GenerateLogFile()
{
  if (s_instance == nullptr)
  {
    std::cout << "[LogFileManager][Error] Instance of LogsFileManager does not exists.\n";
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

  std::cout << timeFilePath << "\n";
}