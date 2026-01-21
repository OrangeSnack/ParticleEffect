#pragma once
#include <cstdint>
#include <string>
#include <filesystem>

namespace MMMEngine::Editor
{
    struct Project
    {
        std::string rootPath;     // 엔진 내부용 ("/" 구분자)
        uint32_t lastSceneIndex;
        std::filesystem::path ProjectRootFS() const
        {
            return std::filesystem::path(rootPath);
        }
    };
}