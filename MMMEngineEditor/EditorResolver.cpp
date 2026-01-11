#include "EditorResolver.h"

bool MMMEngine::Editor::EditorResolver::Resolve(std::string_view sourcePath, MMMEngine::AssetEntry& out) const
{
    if (!m_db) return false;

    MetaFile meta{};
    if (!m_db->TryResolve(sourcePath, meta)) return false;

    out.muid = meta.muid;
    out.cacheType = MMMEngine::AssetEntry::CacheType::File;
    out.filePath = meta.artifactPath;
    out.offset = 0;
    out.size = 0;
    return true;
}


bool MMMEngine::Editor::EditorResolver::Resolve(const Utility::MUID& muid, AssetEntry& out) const
{
    if (!m_db) return false;

    MetaFile meta{};
    if (!m_db->TryResolve(muid, meta))
        return false;

    out.muid = muid;
    out.cacheType = MMMEngine::AssetEntry::CacheType::File;
    out.filePath = meta.artifactPath;
    out.offset = 0;
    out.size = 0;
    return true;
}