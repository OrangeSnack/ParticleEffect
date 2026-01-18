#pragma once
#include <imgui.h>
#include <string>
#include "Singleton.hpp"

namespace MMMEngine::Editor
{
    class StartUpProjectWindow : public Utility::Singleton<StartUpProjectWindow>
    {
    public:
        void Render();

    private:
        // UI state
        std::wstring m_selectedProjectFile; // project.json 경로
        std::wstring m_selectedProjectRoot; // 새 프로젝트 루트 폴더

        // error popup state
        bool m_openErrorPopup = false;
        std::string m_errorMsg;

        void ShowError(const char* msg);
        void RenderErrorPopup();
    };
}