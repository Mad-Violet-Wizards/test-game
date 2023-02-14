#pragma once

class LogFileManager
{

public:

  ~LogFileManager();

  static LogFileManager &GetInstance();

  void CreateLogDirectory();

  void CreateLogFile(const std::string &fileName);

  const std::string &GetLogFilePath(const std::string &filename) const;
  bool DoesLogFileExists(const std::string &logFile) const;

private:

  LogFileManager();

private:

  static std::unique_ptr<LogFileManager> s_instance;
  std::unordered_map<std::string, std::string> m_logFiles;

};