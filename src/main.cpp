#include <iostream>

#include <string>

#include "Time/DateTime.hpp"

int main()
{
    DateTime dt;
    std::string test = dt.GetCurrentDateAndTime();
    std::cout << test << "\n";
}