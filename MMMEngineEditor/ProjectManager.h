#pragma once
#include "Singleton.hpp"
#include "Project.h"
#include <optional>
#include <filesystem>

namespace MMMEngine::Editor
{
    class ProjectManager : public Utility::Singleton<ProjectManager>
    {
    public:
        // 에디터 시작 시
        bool Boot(); // 참 반환 시 프로젝트는 준비된 상태

        bool HasActiveProject() const;
        const Project& GetActiveProject() const;

        // Project operations
        bool OpenProject(const std::filesystem::path& projectFile);
        bool CreateNewProject(const std::filesystem::path& projectRootDir);

        std::optional<std::filesystem::path> SaveActiveProject(); // 저장 경로는 projectRoot/ProjectSettings/project.json 등으로 고정 추천

    private:
        std::optional<Project> m_project;

        // internal helpers
        std::filesystem::path GetProjectFilePath(const std::filesystem::path& root) const;
        void EnsureProjectFolders(const std::filesystem::path& root) const;

        // template generation
        bool GenerateUserScriptsSolution(const std::filesystem::path& projectRootDir) const;

    };
}