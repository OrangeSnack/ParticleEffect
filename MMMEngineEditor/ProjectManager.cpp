#include "ProjectManager.h"
#include <fstream>
#include <filesystem>
#include <json/json.hpp>

using json = nlohmann::json;

namespace fs = std::filesystem;

namespace MMMEngine::Editor
{
    static fs::path GetEditorConfigPath()
    {
        const char* appdata = std::getenv("APPDATA");
        fs::path base = appdata ? fs::path(appdata) : fs::current_path();
        fs::path dir = base / "MMMEngine" / "Editor";
        fs::create_directories(dir);
        return dir / "editor.json";
    }

    static void SaveLastProjectFile(const fs::path& projectFile)
    {
        fs::path cfg = GetEditorConfigPath();
        json j;
        j["lastProjectFile"] = projectFile.generic_u8string(); // '/' + UTF-8
        std::ofstream out(cfg, std::ios::binary);
        if (out) out << j.dump(4);
    }

    bool ProjectManager::HasActiveProject() const
    {
        return m_project.has_value();
    }

    const Project& ProjectManager::GetActiveProject() const
    {
        assert(m_project.has_value());
        return *m_project;
    }

    fs::path ProjectManager::GetProjectFilePath(const fs::path& root) const
    {
        return root / "ProjectSettings" / "project.json";
    }

    void ProjectManager::EnsureProjectFolders(const fs::path& root) const
    {
        fs::create_directories(root / "ProjectSettings");
        fs::create_directories(root / "Assets" / "Scenes");
        fs::create_directories(root / "Source");
        fs::create_directories(root / "Binaries" / "Win64");
        fs::create_directories(root / "Build");
    }

    std::optional<fs::path> ProjectManager::SaveActiveProject()
    {
        if (!m_project) return std::nullopt;

        fs::path root = fs::path(m_project->rootPath);
        EnsureProjectFolders(root);

        fs::path projFile = GetProjectFilePath(root).generic_wstring();

        json j;
        j["rootPath"] = root.generic_u8string();
        j["lastSceneIndex"] = m_project->lastSceneIndex;

        std::ofstream out(projFile, std::ios::binary);
        if (!out) return std::nullopt;

        out << j.dump(4);
        return projFile;
    }


    bool ProjectManager::OpenProject(const fs::path& projectFile)
    {
        if (!fs::exists(projectFile) || !fs::is_regular_file(projectFile))
            return false;

        json j;
        {
            std::ifstream in(projectFile, std::ios::binary);
            if (!in) return false;
            try { in >> j; }
            catch (...) { return false; }
        }

        // projectFile 기준 root (권장)
        fs::path root = projectFile.parent_path().parent_path();

        // json 검증
        if (!j.contains("lastSceneIndex") || !j["lastSceneIndex"].is_number_unsigned())
            return false;

        // json rootPath가 있으면 참고(불일치 시 file 기준 우선)
        if (j.contains("rootPath") && j["rootPath"].is_string())
        {
            fs::path jsonRoot = fs::path(j["rootPath"].get<std::string>());
            if (!jsonRoot.empty() && fs::equivalent(root, jsonRoot) == false)
            {
                // 여기서는 root를 file 기준으로 유지 (정책)
            }
        }

        Project p;
        p.rootPath = root.generic_u8string(); // 엔진 내부는 '/' 유지
        p.lastSceneIndex = j["lastSceneIndex"].get<uint32_t>();

        EnsureProjectFolders(root);
        m_project = p;
        SaveLastProjectFile(projectFile);

        return true;
    }


    bool ProjectManager::CreateNewProject(const fs::path& projectRootDir)
    {
        if (projectRootDir.empty()) return false;

        EnsureProjectFolders(projectRootDir);

        Project p;
        p.rootPath = projectRootDir.generic_u8string();
        p.lastSceneIndex = 0;
        m_project = p;

        auto saved = SaveActiveProject();
        if (!saved) return false;
        if (!GenerateUserScriptsSolution(projectRootDir)) return false;

        SaveLastProjectFile(*saved);
        return true;
    }

    bool ProjectManager::GenerateUserScriptsSolution(const fs::path& projectRootDir) const
    {
        // 일단 넘기기
        return true;
        // 1) 템플릿 경로 찾기
        // TODO: 엔진 실행 경로 기준으로 계산 (예: fs::current_path() 또는 별도 PathManager)
        fs::path templateDir = fs::current_path() / "Templates" / "UserScriptsTemplate";

        if (!fs::exists(templateDir)) return false;

        // 2) 대상 경로
        fs::path dstDir = projectRootDir / "Source" / "UserScripts";
        fs::create_directories(dstDir);

        // 3) 템플릿 폴더 전체 복사
        for (auto& entry : fs::recursive_directory_iterator(templateDir))
        {
            const auto rel = fs::relative(entry.path(), templateDir);
            const auto dst = dstDir / rel;

            if (entry.is_directory())
            {
                fs::create_directories(dst);
            }
            else if (entry.is_regular_file())
            {
                fs::create_directories(dst.parent_path());
                fs::copy_file(entry.path(), dst, fs::copy_options::overwrite_existing);
            }
        }

        // 4) (선택) sln/vcxproj placeholder 치환
        // TODO: __PROJECT_ROOT__ 같은 토큰을 projectRootDir로 replace
        return true;
    }


    bool ProjectManager::Boot()
    {
        // 최근 프로젝트 자동 오픈만 시도
        fs::path cfg = GetEditorConfigPath();
        if (!fs::exists(cfg))
            return false;

        json j;
        {
            std::ifstream in(cfg, std::ios::binary);
            if (!in) return false;
            try { in >> j; }
            catch (...) { return false; }
        }

        if (!j.contains("lastProjectFile") || !j["lastProjectFile"].is_string())
            return false;

        fs::path lastProj = fs::path(j["lastProjectFile"].get<std::string>());
        if (!fs::exists(lastProj))
            return false;

        return OpenProject(lastProj);
    }

}
