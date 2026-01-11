#include "FileBytesProvider.h"

bool MMMEngine::Editor::FileBytesProvider::ReadAll(const MMMEngine::AssetEntry& entry, std::vector<uint8_t>& outBytes)
{
    if (entry.cacheType != MMMEngine::AssetEntry::CacheType::File) return false;

    std::ifstream f(entry.filePath, std::ios::binary);
    if (!f) return false;

    f.seekg(0, std::ios::end);
    const auto sz = f.tellg();
    if (sz < 0) return false;
    f.seekg(0, std::ios::beg);

    outBytes.resize((size_t)sz);
    if (sz > 0) f.read((char*)outBytes.data(), sz);
    return (bool)f;
}