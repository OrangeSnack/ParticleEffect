#pragma once
#pragma once
#include "MUID.h"
#include <cstdint>
#include <string>

namespace MMMEngine
{
    struct AssetEntry
    {
        Utility::MUID muid{};

        enum class CacheType : uint8_t { File = 0, Pak = 1 };
        CacheType cacheType = CacheType::File;

        // File
        std::wstring filePath; // artifact 실제 경로(에디터)

        // Pak
        uint64_t offset = 0;
        uint64_t size = 0;
    };
}
