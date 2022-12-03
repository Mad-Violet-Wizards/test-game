#pragma once

#include <fstream>
#include <mutex>

#include "LogFileManager.hpp"
#include "ConsoleLog.hpp"

static std::mutex fileLogMutex;

template <typename T>
constexpr static void FILE_LOG(const std::string &filename, const T &msg)
{
  {
    std::unique_lock lock(fileLogMutex);
    if (!LogFileManager::GetInstance().DoesLogFileExists(filename))
    {
      CONSOLE_LOG("Creatg log file: " + filename);
      LogFileManager::GetInstance().CreateLogFile(filename);
      CONSOLE_LOG("Filepath: ", LogFileManager::GetInstance().GetLogFilePath(filename));
    }

    std::ofstream logFile(LogFileManager::GetInstance().GetLogFilePath(filename), std::ios_base::app);

    auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

    const auto formattedMsg = std::format("[{:%Y/%m/%d %H:%M:%S}]{}",
                                          std::chrono::floor<std::chrono::milliseconds>(time),
                                          msg);

    logFile << formattedMsg
            << "\n"
            << std::flush;

    logFile.close();
  }
}

template <typename ...Args>
constexpr static void FILE_LOG(const std::string &filename, const std::string &prefix, Args &&... args)
{
  {
    std::unique_lock lock(fileLogMutex);

    if (!LogFileManager::GetInstance().DoesLogFileExists(filename))
    {
      CONSOLE_LOG("Creatg log file: " + filename);
      LogFileManager::GetInstance().CreateLogFile(filename);
      CONSOLE_LOG("Filepath: ", LogFileManager::GetInstance().GetLogFilePath(filename));
    }
    
    std::ofstream logFile(LogFileManager::GetInstance().GetLogFilePath(filename), std::ios_base::app);
    auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

    logFile << std::format("[{:%Y/%m/%d %H:%M:%S}]", std::chrono::floor<std::chrono::milliseconds>(time)) << prefix;

    ((logFile << std::forward<Args>(args) << " "), ...);

    logFile << "\n" << std::flush;

    logFile.close();
    }
}

#define FILE_LOG_INFO(LOG_FILENAME, ...)    FILE_LOG(LOG_FILENAME, "[Info] ",    __VA_ARGS__);
#define FILE_LOG_WARNING(LOG_FILENAME, ...) FILE_LOG(LOG_FILENAME, "[Warning] ", __VA_ARGS__);
#define FILE_LOG_ERROR(LOG_FILENAME, ...)   FILE_LOG(LOG_FILENAME, "[Error] ",   __VA_ARGS__);
#define FILE_LOG_DEBUG(LOG_FILENAME, ...)   FILE_LOG(LOG_FILENAME, "[Debug] ",   __VA_ARGS__);