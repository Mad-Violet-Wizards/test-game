#pragma once

#include <string>
#include <stdexcept>
#include <iostream>
#include <iomanip>
#include <sstream>
#include <zlib.h>
#include <vector>
#include <regex>
#include <fstream>

class Compressor
{

public:
  
  Compressor() = default;
  ~Compressor() = default;

  static int s_Progress;

  static void ShowProgress(int progress, int totalFiles);

  static void CompressPathes(const std::vector<std::string> &pathes);
  static void DecompressPathes(const std::vector<std::string> &pathes);

  static std::string CompressString(const std::string &str, int compressionlevel = Z_BEST_COMPRESSION);
  static std::string DecompressString(const std::string &str);

private:

  static std::string ReplaceFileExtension(const std::string &path, const std::string &newExtension);

};