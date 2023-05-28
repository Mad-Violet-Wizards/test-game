#pragma once

#include "Design-Patterns/Singleton.hpp"

class LogFileManager
{

public:

  LogFileManager();
  ~LogFileManager() = default;

  void CreateLogDirectory();

  void CreateLogFile(const std::string &fileName);

  const std::string &GetLogFilePath(const std::string &filename) const;
  bool DoesLogFileExists(const std::string &logFile) const;

private:

  std::unordered_map<std::string, std::string> m_logFiles;

};

using LogFileManagerSingleton = Singleton<LogFileManager>;