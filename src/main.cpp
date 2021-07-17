#include <iostream>
#include <string>
#include <unistd.h>

#include "Logs/Logs.hpp"
#include "Time/DateTime.hpp"

int main()
{
  Logs l1;
  l1.LogToConsoleNewLine("Test123", "123");
}