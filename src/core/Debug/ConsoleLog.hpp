#pragma once

template <typename T>
constexpr static inline void CONSOLE_LOG(const T &msg)
{
  thread_local std::osyncstream sync_cout(std::cout);

  std::cout << msg
            << "\n"
            << std::flush;
}

template <typename ...Args>
constexpr static inline void CONSOLE_LOG(const std::string &prefix, Args &&... args)
{
  thread_local std::osyncstream sync_cout(std::cout);

  std::cout << prefix;

  ((std::cout << std::forward<Args>(args) << " "), ...);

  std::cout << "\n" << std::flush;
}

#define CONSOLE_LOG_INFO(...)    CONSOLE_LOG("[Info] ",    __VA_ARGS__);
#define CONSOLE_LOG_WARNING(...) CONSOLE_LOG("[Warning] ", __VA_ARGS__);
#define CONSOLE_LOG_ERROR(...)   CONSOLE_LOG("[Error] ",   __VA_ARGS__);
#define CONSOLE_LOG_DEBUG(...)   CONSOLE_LOG("[Debug] ",   __VA_ARGS__);