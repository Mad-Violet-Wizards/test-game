#pragma once

#include <iostream>
#include <fstream>
#include <string>

#include "DateTime.hpp"

static std::string g_currentLogFileName = "";

class Logs
{

  public:
  
      Logs();
      ~Logs();
      
      /*
      * INTERFACE TO LOG INTO .TXT FILE
      */
      Logs& operator<<(const char* value);
      Logs& operator<<(const std::string& value);
      Logs& operator<<(const int value);
      Logs& operator<<(const double value);

      /*
      * INTERFACE TO LOG INTO CONSOLE
      */
      template<typename ...Args>
      void LogToConsole(Args&&... args) noexcept
      {
        ((std::cout << std::forward<Args>(args) << "\t"), ...);
      }


      template <typename ...Args>
      void LogToConsoleNewLine(Args&&... args) noexcept
      {
        ((std::cout << std::forward<Args>(args) << "\n"), ...);
      }

  private:

      void Init();

      std::string DateTimePrefix();

      std::ofstream m_logFile;
};
