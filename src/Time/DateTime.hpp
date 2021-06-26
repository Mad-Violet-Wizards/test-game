#include <ctime>
#include <string>

class DateTime
{

public:
    DateTime();
    ~DateTime();

    std::string GetCurrentDate() const;
    std::string GetCurrentTime() const;
    std::string GetCurrentDateAndTime() const;

};