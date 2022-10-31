#pragma once

#include <vector>
#include <string>

#include "Directory.hpp"

namespace OnyxTools
{
    namespace Compressor
    {
        class AssetsContainer
        {

        public:

            AssetsContainer();
            ~AssetsContainer();

            void CollectAssets(const std::string &path);
            void CreateOutputDirectory();

            void PrintFoundFiles();

            int Size() const;

            const std::vector<std::string> &GetPathes() const;

        private:

            bool m_isDirectory;
            std::string m_currentPath;
            std::vector<std::string> m_files;
        };
    }
}