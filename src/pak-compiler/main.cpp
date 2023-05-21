#include <fstream>
#include <vector>
#include <string>
#include <iostream>
#include <filesystem>
#include <array>
#include <algorithm>
#include <iterator>
#include "PakFilesystemHeaders.hpp"

void FillFilePathes(const std::string &input, std::vector<std::string> &filePathes)
{
  std::filesystem::path inputPath(input);

  if (!std::filesystem::exists(inputPath)) [[unlikely]]
  {
    std::cout << "Pak-Compiler: Input directory does not exist.\n";
    return;
  }

  if (std::filesystem::is_directory(inputPath))
  {
    for (const auto& entry : std::filesystem::directory_iterator(inputPath))
    {
        if (std::filesystem::is_directory(entry.path())) [[unlikely]]
        {
          FillFilePathes(entry.path().string(), filePathes);
        }

        if (std::filesystem::is_regular_file(entry.path()) /* & CHECK COMPABILITY WITH ENGINE? */) [[likely]]
        {
          std::string fp_no_back_slashes = entry.path().string();
          std::replace(fp_no_back_slashes.begin(), fp_no_back_slashes.end(), '\\', '/');

          if (std::find(filePathes.cbegin(), filePathes.cend(), fp_no_back_slashes) != filePathes.cend()) [[unlikely]]
          {
            std::cout << "Pak-Compiler: File with same name already exists: " << fp_no_back_slashes << "\n";
            continue;
          }

          filePathes.push_back(fp_no_back_slashes);
        }
    }
  }
}

void WritePakFile(const std::string &inputDirectoryPath, const std::string &outputPakPath)
{
  std::cout << "Pak-Compiler: Input directory: " << inputDirectoryPath << "\n";
  std::cout << "Pak-Compiler: Output pak filename: " << outputPakPath << "\n";

  std::ofstream pakFile(outputPakPath, std::ios::binary);

  std::vector<std::string> filePathes;
  FillFilePathes(inputDirectoryPath, filePathes);

  PakFile_HeaderMetadata headerMetadata(filePathes.size(), 1);

  pakFile.write(reinterpret_cast<char*>(&headerMetadata), sizeof(PakFile_HeaderMetadata));

  std::vector<PakFile_EntryMetadata> entryMetadata(filePathes.size());

  for (auto i = 0; i < filePathes.size(); ++i)
  {
    const std::string& filePath = filePathes[i];
    PakFile_EntryMetadata& entry = entryMetadata[i];

    std::copy(filePath.cbegin(), filePath.cend(), entry.m_filePath.data());

    std::ifstream inputFile(filePath, std::ios::binary);

    inputFile.seekg(0, std::ios::end);

    entry.m_size = inputFile.tellg();

    inputFile.seekg(0, std::ios::beg);

    entry.m_offset = pakFile.tellp();

    pakFile.write(reinterpret_cast<char*>(&entry), sizeof(PakFile_EntryMetadata));

    std::vector<uint8_t> buffer(entry.m_size);

    inputFile.read(reinterpret_cast<char*>(buffer.data()), entry.m_size);

    pakFile.write(reinterpret_cast<char*>(buffer.data()), entry.m_size);
  }
}

int main(int *argc, char **argv)
{
  std::cout << "Pak-Compiler: Hello world.\n";

  std::string inputDirectory = argv[1];
  std::string outputPakFilepath = argv[2];

  if (inputDirectory.empty()) [[unlikely]]
  {
    std::cout << "Pak-Compiler: No input directory specified.\n";
    return EXIT_FAILURE;
  }

  if (outputPakFilepath.empty()) [[unlikely]]
  {
    std::cout << "Pak-Compiler: No output pak filename specified.\n";
    return EXIT_FAILURE;
  }

  WritePakFile(inputDirectory, outputPakFilepath);

  return EXIT_SUCCESS;
}