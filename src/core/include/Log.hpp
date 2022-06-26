#pragma once

#include <iostream>
#include <fstream>
#include <filesystem>

static std::string s_logFile;

class Log : private std::streambuf, public std::ostream
{

public:

  Log() : std::ostream(this) {}

private:

  int overflow(int c) override
  {
    SaveToFile(c);
    return 0;
  }

  void SaveToFile(char txt)
  {
    if (s_logFile.empty())
    {
      GenerateLogDirectoryWithFile();
    }

    std::ofstream ofs;
    ofs.open(s_logFile, std::ios_base::app);
    ofs << txt; 
    ofs.close();
  }

  void GenerateLogDirectoryWithFile()
  {
    std::filesystem::path path{ "../../logs" };

    path /= "log.txt";

    std::filesystem::create_directories(path.parent_path());

    s_logFile = path.string();
  }
};