#include <string>

#pragma once

class JsonHandler
{

public:

  JsonHandler();
  ~JsonHandler();

  void LoadFile(const std::string &filePath);

  const char *GetJsonContent() const;

private:

  char *m_jsonFileContent;

};