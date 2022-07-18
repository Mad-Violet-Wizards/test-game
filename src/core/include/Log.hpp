#pragma once

#include <fstream>

#include "LogFileManager.hpp"

template <typename T>
constexpr void LOG(const T &msg)
{
  LogFileManager::GetInstance().CreateLogDirectory();
  LogFileManager::GetInstance().CreateLogFile();

  std::ofstream logFile(LogFileManager::GetInstance().GetLogFilePath(), std::ios_base::app);

  auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

  const auto formattedMsg = std::format("[{:%Y/%m/%d %H:%M:%S}]{}",
                                        std::chrono::floor<std::chrono::milliseconds>(time),
                                        msg);

	logFile << formattedMsg
          << "\n"
          << std::flush;

  logFile.close();
}

template <typename ...Args>
constexpr void LOG(const std::string &prefix, Args &&... args)
{
  LogFileManager::GetInstance().CreateLogDirectory();
  LogFileManager::GetInstance().CreateLogFile();

  std::ofstream logFile(LogFileManager::GetInstance().GetLogFilePath(), std::ios_base::app);

  auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

  logFile << std::format("[{:%Y/%m/%d %H:%M:%S}]", std::chrono::floor<std::chrono::milliseconds>(time)) << prefix;

	((logFile << std::forward<Args>(args) << " "), ...);

  logFile << "\n" << std::flush;

  logFile.close();
}

#define LOG_INFO(...)    LOG("[Info] ",    __VA_ARGS__);
#define LOG_WARNING(...) LOG("[Warning] ", __VA_ARGS__);
#define LOG_ERROR(...)   LOG("[Error] ",   __VA_ARGS__);
#define LOG_DEBUG(...)   LOG("[Debug] ",   __VA_ARGS__);