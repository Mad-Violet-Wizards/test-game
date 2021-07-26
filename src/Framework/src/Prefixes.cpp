#include "Prefixes.hpp"

const std::string Prefixes::OnyxCorePrefix()
{
  return "[Onyx Core] ";
}

const std::string Prefixes::OnyxFrameworkPrefix()
{
  return "[Onyx Framework] ";
}

const std::string Prefixes::OnyxGamePrefix()
{
  return "[Onyx Game] ";
}

const std::string Prefixes::DateTimePrefix()
{
  return "[" + DateTime::GetCurrentDateAndTime() + "] ";
}