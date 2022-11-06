#pragma once

#include <fstream>

#include "LogFileManager.hpp"

template <typename T>
constexpr static inline void FILE_LOG(const T &msg)
{
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
constexpr static inline void FILE_LOG(const std::string &prefix, Args &&... args)
{
  std::ofstream logFile(LogFileManager::GetInstance().GetLogFilePath(), std::ios_base::app);

  auto const time = std::chrono::current_zone() -> to_local(std::chrono::system_clock::now());

  logFile << std::format("[{:%Y/%m/%d %H:%M:%S}]", std::chrono::floor<std::chrono::milliseconds>(time)) << prefix;

	((logFile << std::forward<Args>(args) << " "), ...);

  logFile << "\n" << std::flush;

  logFile.close();
}

#define FILE_LOG_INFO(...)    FILE_LOG("[Info] ",    __VA_ARGS__);
#define FILE_LOG_WARNING(...) FILE_LOG("[Warning] ", __VA_ARGS__);
#define FILE_LOG_ERROR(...)   FILE_LOG("[Error] ",   __VA_ARGS__);
#define FILE_LOG_DEBUG(...)   FILE_LOG("[Debug] ",   __VA_ARGS__);