#include <iostream>

#include <string>

#include "Time/DateTime.hpp"
#include <unistd.h>

int main()
{
    DateTime dt;
    std::string test = dt.GetCurrentDateAndTime();
    std::cout << test << "\n";
    usleep(3000000);
    test = dt.GetCurrentDateAndTime();
    std::cout << test << "\n";
}