#include <iostream>
#include <fstream>

#include "JsonHandler.hpp"

JsonHandler::JsonHandler() { }

JsonHandler::~JsonHandler() 
{ 
  if (m_jsonFileContent != nullptr)
  {
    delete m_jsonFileContent;
  }
}

void JsonHandler::LoadFile(const std::string &filePath)
{
  if (m_jsonFileContent != nullptr)
  {
    std::cout << "[JsonHandler] File already lodaded.\n";
    return;
  }

  std::ifstream jsonFileStream;
  jsonFileStream.open(filePath);

  std::string jsonData, line;

  while(std::getline(jsonFileStream, line))
  {
    jsonData += line;
  }

  jsonFileStream.close();

  const char *jsonRawData = jsonData.c_str();

  m_jsonFileContent = new char[strlen(jsonRawData) + 1];
  
  strcpy_s(m_jsonFileContent, strlen(jsonRawData) + 1, jsonRawData);
}

const char *JsonHandler::GetJsonContent() const
{
  return m_jsonFileContent;
}