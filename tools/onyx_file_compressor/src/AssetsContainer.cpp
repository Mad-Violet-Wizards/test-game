#include "AssetsContainer.hpp"

#include <filesystem>
#include <regex>
#include <cstring>

#include "Log.hpp"

OnyxTools::Compressor::AssetsContainer::AssetsContainer() 
    : m_isDirectory(false),
      m_currentPath({ASSETS_DIRECTORY_INPUT})
{
}


OnyxTools::Compressor::AssetsContainer::~AssetsContainer()
{
    // Delete everything.
}

void OnyxTools::Compressor::AssetsContainer::CollectAssets(const std::string &path)
{
    if (std::filesystem::exists(path))
    {
        for (const auto &entry : std::filesystem::directory_iterator(path))
        {
            if (std::filesystem::is_directory(entry))
            {
                auto directory_path = path + std::filesystem::path(entry).filename().generic_string() + "/";
                CollectAssets(directory_path);
            }
            else
            {
                auto file_path = path + std::filesystem::path(entry).filename().generic_string();
                m_files.push_back(std::move(file_path));
            }
        }
    }
    else
    {
        LOG("Path does not exists.");
    }
}

void OnyxTools::Compressor::AssetsContainer::PrintFoundFiles()
{
    for (const auto &file : m_files)
    {
        LOG("File path: ", file);
    }
}

int OnyxTools::Compressor::AssetsContainer::Size() const
{
    return m_files.size();
}

const std::vector<std::string> &OnyxTools::Compressor::AssetsContainer::GetPathes() const
{
    return m_files;
}

void OnyxTools::Compressor::AssetsContainer::CreateOutputDirectory()
{
    for (const std::string &file : m_files)
    {
        // Delete the last part of the path.
        const std::string directory = file.substr(0, file.find_last_of("/")); 

        // Replace the assets_raw with assets_compressed
        const std::string outputPath = std::regex_replace(directory, std::regex(ASSETS_DIRECTORY_INPUT), ASSETS_DIRECTORY_OUTPUT);

        if (!std::filesystem::exists(outputPath))
        {
            std::filesystem::create_directories(outputPath);
        }
    }
}